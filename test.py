import os
import sys
import subprocess
import pexpect
import re

# Color constants for terminal output
COLORS = {
    "GREEN": "\033[92m",
    "RED": "\033[91m",
    "MAGENTA": "\033[35m",
    "RESET": "\033[0m",
    "CYAN": "\033[96m",
    "YELLOW": "\033[93m",
    "BLUE": "\033[94m",
    "WHITE": "\033[97m",
}
TESTS = [
    # Basic echo tests
    {"command": "echo", "expected_output": "\n"},
    {"command": "echo Hello, World!", "expected_output": "Hello, World!\n"},
    {"command": "echo -n Hello, World!", "expected_output": "Hello, World!"},
    {"command": "echo \"Hello, World!\"", "expected_output": "Hello, World!\n"},
    {"command": "echo 'Hello, World!'", "expected_output": "Hello, World!\n"},
    {"command": "echo \"'Hello, World!'\"", "expected_output": "'Hello, World!'\n"},
    {"command": "echo '\"Hello, World!\"'", "expected_output": "\"Hello, World!\"\n"},
    {"command": "echo -n -n -n Hello, World!", "expected_output": "Hello, World!"},
    {"command": "echo -nnnn Hello, World!", "expected_output": "Hello, World!"},
    {"command": "echo \"\"", "expected_output": "\n"},
    {"command": "echo ''", "expected_output": "\n"},
    {"command": "echo '   '", "expected_output": "   \n"},
    {"command": "echo \"   \"", "expected_output": "   \n"},
    {"command": "echo 'Hello   World'", "expected_output": "Hello   World\n"},
    {"command": "echo \"Hello   World\"", "expected_output": "Hello   World\n"},

    # Environment variable tests
    {"command": "echo $NONEXISTENT", "expected_output": "\n"},
    {"command": "echo 'Hello, $USER!'", "expected_output": "Hello, $USER!\n"},
    {"command": "echo \\$USER", "expected_output": "$USER\n"},
    {"command": "echo \"Hello, \\\"World\\\"!\"", "expected_output": "Hello, \"World\"!\n"},
    {"command": "echo 'Hello, \\'World\\'!'", "expected_output": "Hello, \\'World\\'!\n"},
    {"command": "echo \"Hello, $NONEXISTENT!\"", "expected_output": "Hello, !\n"},
    {"command": "echo 'Hello, $NONEXISTENT!'", "expected_output": "Hello, $NONEXISTENT!\n"},
]

def install_pexpect():
    """
    Install the `pexpect` library if it is not already installed.
    """
    try:
        import pexpect
    except ImportError:
        print(f"{COLORS['YELLOW']}pexpect is not installed. Installing...{COLORS['RESET']}")
        subprocess.check_call([sys.executable, "-m", "pip", "install", "pexpect"])
        print(f"{COLORS['GREEN']}pexpect installed successfully!{COLORS['RESET']}")

def detect_prompt():
    """
    Detect the prompt by running the minishell binary and capturing the first output.
    """
    try:
        minishell = pexpect.spawn("./minishell", encoding="utf-8", timeout=2)
        minishell.expect(r".+\$ ")
        prompt = minishell.after.strip()
        minishell.sendline("exit")
        minishell.wait()
        return prompt
    except Exception as e:
        print(f"{COLORS['RED']}Error detecting prompt: {e}{COLORS['RESET']}")
        return None

def clean_output(output):
    """
    Clean the output by removing terminal control sequences, carriage returns, and normalizing newlines.
    """
    # Remove ANSI escape sequences (e.g., \x1b[?2004l)
    ansi_escape = re.compile(r"\x1b\[.*?m|\x1b\[.*?l|\x1b\[.*?h|\x1b\[.*?K")
    output = ansi_escape.sub("", output)
    
    # Remove carriage returns (\r)
    output = output.replace("\r", "")
    
    # Normalize newlines
    output = output.replace("\r\n", "\n").replace("\r", "\n")
    
    # Strip leading/trailing whitespace
    output = output.strip()
    
    return output

def run_test(test_id, command, expected_output, prompt):
    """
    Run a single test case and compare the output with the expected output.
    """
    try:
        # Spawn the minishell process
        minishell = pexpect.spawn("./minishell", encoding="utf-8", timeout=2)
        
        # Escape the prompt to avoid regex issues
        escaped_prompt = re.escape(prompt)
        minishell.expect(escaped_prompt)
        
        # Send the command
        minishell.sendline(command)
        minishell.expect(escaped_prompt)
        
        # Extract and clean the output
        output = minishell.before
        
        # Remove the input command from the output
        output_lines = output.split("\n")
        if output_lines[0].strip() == command.strip():
            output_lines.pop(0)  # Remove the first line (input command)
        output = "\n".join(output_lines).strip()
        
        # Clean the output (remove terminal control sequences, etc.)
        output = clean_output(output)
        
        # Close the minishell process
        minishell.sendline("exit")
        minishell.wait()
        
        # Compare the output with the expected output
        if output == expected_output.strip():
            print(f"{COLORS['GREEN']}[OK]{COLORS['RESET']} {COLORS['CYAN']}Test {test_id}: {command}{COLORS['RESET']}")
        else:
            print(f"{COLORS['RED']}[KO]{COLORS['RESET']} {COLORS['CYAN']}Test {test_id}: {command}{COLORS['RESET']}")
        
        # Debug: Print raw output and expected output
        print(f"{COLORS['MAGENTA']}Expected (raw):{COLORS['RESET']} {repr(expected_output)}")
        print(f"{COLORS['MAGENTA']}Got (raw):{COLORS['RESET']} {repr(output)}")
    except pexpect.exceptions.ExceptionPexpect as e:
        print(f"{COLORS['RED']}[ERROR]{COLORS['RESET']} {COLORS['CYAN']}Test {test_id}: {command}{COLORS['RESET']}")
        print(f"Error: {e}")

def main():
    """
    Main function to run all test cases.
    """
    # Install pexpect if not already installed
    install_pexpect()

    # Detect or ask for the prompt
    prompt = detect_prompt()
    if not prompt:
        prompt = input(f"{COLORS['CYAN']}Enter your minishell prompt (e.g., 'minishell$ '): {COLORS['RESET']}").strip()

    # Run all tests
    for i, test in enumerate(TESTS, start=1):
        run_test(i, test["command"], test["expected_output"], prompt)

if __name__ == "__main__":
    main()
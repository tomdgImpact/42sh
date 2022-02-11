from argparse import ArgumentParser
from pathlib import Path
from difflib import unified_diff
from dataclasses import dataclass, field

import subprocess as sp
import termcolor
import yaml


# JOLI
OK_TAG = f"{termcolor.colored('[OK]', 'green', attrs=['bold'])}"
KO_TAG = f"{termcolor.colored('[KO]', 'red', attrs=['bold'])}"


def print_title():
    print("\n")
    print("████████╗███████╗███████╗████████╗    ███████╗██╗   ██╗██╗████████╗███████╗")
    print("╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝    ██╔════╝██║   ██║██║╚══██╔══╝██╔════╝")
    print("   ██║   █████╗  ███████╗   ██║       ███████╗██║   ██║██║   ██║   █████╗  ")
    print("   ██║   ██╔══╝  ╚════██║   ██║       ╚════██║██║   ██║██║   ██║   ██╔══╝  ")
    print("   ██║   ███████╗███████║   ██║       ███████║╚██████╔╝██║   ██║   ███████╗")
    print("   ╚═╝   ╚══════╝╚══════╝   ╚═╝       ╚══════╝ ╚═════╝ ╚═╝   ╚═╝   ╚══════╝")
    print("                    ██╗  ██╗██████╗ ███████╗██╗  ██╗                       ")
    print("                    ██║  ██║╚════██╗██╔════╝██║  ██║                       ")
    print("                    ███████║ █████╔╝███████╗███████║                       ")
    print("                    ╚════██║██╔═══╝ ╚════██║██╔══██║                       ")
    print("                         ██║███████╗███████║██║  ██║                       ")
    print("                         ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝                       ")
    print("                                                                           ")
    return


@dataclass
class TestCase:
    name: str
    stdin: str
    checks: list[str] = field(default_factory=lambda: ["stdout", "stderr", "exitcode"])


def diff(expected: str, actual: str) -> str:
    expected_lines = expected.splitlines(keepends=True)
    actal_lines = actual.splitlines(keepends=True)
    return "".join(
        unified_diff(expected_lines, actal_lines, fromfile="expected", tofile="actual")
    )


def check_return(expected: sp.CompletedProcess, actual: sp.CompletedProcess, checks):
    assert (
        "has_stderr" not in checks or actual.stderr != ""
    ), "Something was expecting on STDERR"

    assert (
        "exitcode" not in checks or expected.returncode == actual.returncode
    ), f"Exited with {actual.returncode} expected {expected.returncode}"

    assert (
        "stdout" not in checks or expected.stdout == actual.stdout
    ), f"Error: NOT THE SAME STDOUT\n{diff(expected.stdout, actual.stdout)}"

    assert (
        "stderr" not in checks or expected.stderr == actual.stderr
    ), f"Error: NOT THE SAME STDERR\n{diff(expected.stderr, actual.stderr)}"


def run_shell(shell: str, stdin: str) -> sp.CompletedProcess:
    return sp.run([shell], input=stdin, capture_output=True, text=True)


if __name__ == "__main__":
    parser = ArgumentParser("Testsuite")
    parser.add_argument("--binary", required=True, type=Path)
    args = parser.parse_args()

    binary_path = args.binary.absolute()
    print(f"Testing: {binary_path}")

    with open("test.yml", "r") as file:
        testSuite = [TestCase(**testCase) for testCase in yaml.safe_load(file)]

    print_title()

    for testCase in testSuite:
        stdin = testCase.stdin
        name = testCase.name

        bash_proc = run_shell("bash", stdin)
        sh_proc = run_shell(binary_path, stdin)

        print(bash_proc.stdout)
        print(sh_proc.stdout)

        try:
            check_return(bash_proc, sh_proc, testCase.checks)
        except AssertionError as err:
            print(f"{KO_TAG} {name}\n{err}")
        else:
            print(f"{OK_TAG} {name}")

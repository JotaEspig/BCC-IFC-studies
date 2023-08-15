package shell

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"os/exec"
	"os/user"
	"strings"

	"github.com/fatih/color"
)

var (
	green   = color.New(color.FgGreen)
	magenta = color.New(color.FgMagenta)
)

type Shell struct {
	pwd             string
	scanner         *bufio.Scanner
	lastEntryCmdStr string
	lastErr         error
}

func NewShell() *Shell {
	pwd, err := os.Getwd()
	if err != nil {
		log.Fatalln(err)
		panic(err)
	}

	scanner := bufio.NewScanner(os.Stdin)

	return &Shell{pwd, scanner, "", nil}
}

func (s *Shell) readInput() {
	ok := s.scanner.Scan()
	s.lastEntryCmdStr = s.scanner.Text()
	if !ok {
		s.lastErr = io.EOF
		if err := s.scanner.Err(); err != nil {
			s.lastErr = err
		}
	}
}

func (s *Shell) printUserPwd() {
	user, err := user.Current()
	if err != nil {
		log.Fatalln(err)
		panic(err)
	}

	folder := s.pwd[strings.LastIndex(s.pwd, "/"):len(s.pwd)]
	green.Print(user.Username)
	fmt.Print(" (")
	magenta.Print(folder)
	fmt.Print(")# ")
}

func (s *Shell) printCommand(cmd *exec.Cmd) {
	stdout, _ := cmd.StdoutPipe()
	stderr, _ := cmd.StderrPipe()
	cmd.Start()

	stdoutScanner := bufio.NewScanner(stdout)
	stderrScanner := bufio.NewScanner(stderr)
	for stdoutScanner.Scan() {
		m := stdoutScanner.Text()
		fmt.Println(m)

		stderrScanner.Scan()
		m = stderrScanner.Text()
		if m != "" {
			fmt.Println(m)
		}
	}

	cmd.Wait()
}

func (s *Shell) shouldExit() bool {
	return s.lastEntryCmdStr == "exit" || s.lastErr == io.EOF
}

func (s *Shell) Run() {
	for {
		s.printUserPwd()
		s.readInput()
		if s.shouldExit() {
			fmt.Println()
			break
		}

		cmdSplited := strings.Split(s.lastEntryCmdStr, " ")
		cmdStr := cmdSplited[0]
		var cmdArgs []string
		if len(cmdSplited) > 1 {
			cmdArgs = cmdSplited[1:]
		}

		cmd := exec.Command(cmdStr, cmdArgs...)
		s.printCommand(cmd)
	}
}

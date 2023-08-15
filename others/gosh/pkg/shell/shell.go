package shell

import (
	"fmt"
	"io"
	"log"
	"os"
	"os/exec"
)

type Shell struct {
	pwd             string
	lastEntryCmdStr string
	lastErr         error
}

func NewShell() *Shell {
	pwd, err := os.Getwd()
	if err != nil {
		log.Fatalln(err)
		panic(err)
	}

	return &Shell{pwd, "", nil}
}

func (s *Shell) shouldExit() bool {
	return s.lastEntryCmdStr == "exit" || s.lastErr == io.EOF
}

func (s *Shell) Run() {
	for {
		fmt.Print("> ")
		_, s.lastErr = fmt.Scanln(&s.lastEntryCmdStr)
		if s.shouldExit() {
			break
		}

		combinedOutput, err := exec.Command(s.lastEntryCmdStr).CombinedOutput()
		if err != nil {
			fmt.Println(err)
		} else {
			fmt.Print(string(combinedOutput))
		}
	}
}

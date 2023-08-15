package shell

import (
	"errors"
	"os"
)

type fnCmd func(s *Shell, args ...string) error

var commands map[string]fnCmd = make(map[string]fnCmd)

func change_dir(s *Shell, args ...string) error {
	if len(args) == 0 {
		return errors.New("cd: invalid amount of arguments")
	}

	err := os.Chdir(args[0])
	if err != nil {
		return err
	}

	pwd, err := os.Getwd()
	if err != nil {
		return err
	}
	s.pwd = pwd
	return nil
}

func init() {
	commands["cd"] = change_dir
}

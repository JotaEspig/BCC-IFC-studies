package main

import (
	"fmt"
	"reflect"
)

type Pessoa struct {
	Nome  string
	Email string
	CPF   string
}

func (p Pessoa) Print() {
	fmt.Println(p)
}

type Motorista struct {
	Pessoa
	CNH string
}

func (m Motorista) Print() {
	m.Pessoa.Print()
	fmt.Println(m.CNH)
}

// Função que "descobre" o que é a variável
func discover(x any) {
	value := reflect.ValueOf(x)

	// Tipo da variável
	fmt.Printf("%v %s\n", value.Kind(), value.Type().Name())

	// Tamanho da variavel usando reflexão
	fmt.Println(value.Type().Size())

	// Mostra o atributo nome do objeto utilizando reflexão
	fmt.Println(value.FieldByName("Nome"))

	// Chama o método Print utilizando reflexão
	value.MethodByName("Print").Call([]reflect.Value{})
}

func main() {
	fmt.Printf("Hello\n\n")

	p := Pessoa{"Jairo", "jairo@jairo.com", "11111111111"}
	discover(p)

	fmt.Println()

	m := Motorista{p, "1"}
	discover(m)
}

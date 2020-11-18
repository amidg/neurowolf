package main //THIS IS TEST MAIN

import (
	"fmt"
	//wolfTest "Wolf/Wolf"

	"image"
	_ "image/jpeg"
)

//WILL BE REMOVED LATER INTO A SEPARATE FILE
type Wolf struct {
	name   string
	wisdom string //replace with type wisdom.go later
}

func defaultWolf(newWolfName string, newWolfWisdom string) *Wolf {

	var defaultWisdom = "Wolf is stronger than lion but does not perform in circus"
	newWolfWisdom = defaultWisdom
	w := Wolf{name: newWolfName, wisdom: newWolfWisdom}
	return &w
}

/////////////////////////////////////////////////////////////

func main() {
	wolf := defaultWolf("Default Wolf", " ")
	fmt.Println("Welcome to Wolf Wisdom Generator V0.0.1")
	fmt.Println("We created the default wolf that gives default Wisdom")
	fmt.Println(wolf.name)
	fmt.Println(wolf.wisdom)

	img := image.Image{}
}

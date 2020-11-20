package main //THIS IS TEST MAIN

import (
	"fmt"
	//wolfTest "Wolf/Wolf"

	//required to read image from file

	"image/jpeg"
	"os"
	_ "image/png"
	"image"

	"github.com/fogleman/gg" //needed to draw text on image
)

/////////////////////////////////////////////
//DECLARE VARIABLES:

//image related stuff
wolfImage := image.NewRGBA(image.Rectangle{image.Point{0, 0}, image.Point{100,100}})
var wolfImageErr = 0 //error variable 
var loadedWolfImage = NewUniform(color.black)
var loadedWolfImageErr = 0 //error variable
var pathToWolfImage = "Source/wolfDefault.jpeg" //default wolf

var wolfImgWidth = 0
var wolfImgHeight = 0


/////////////////////////////////////////////
//WILL BE REMOVED LATER INTO A SEPARATE FILE
type Wolf struct {
	name   string
	wisdom string //replace with type wisdom.go later
}

func newWolf(newWolfName string, newWolfWisdom string) *Wolf {

	if newWolfWisdom == "default" {
		var defaultWisdom = "Wolf is stronger than lion but does not perform in circus"
		newWolfWisdom = defaultWisdom
	} else {
		//do nothing
	}

	w := Wolf{name: newWolfName, wisdom: newWolfWisdom}
	return &w
}

/////////////////////////////////////////////////////////////
//FUNCTIONS:
func readAndDecodeImage(importedImagePath string) { //void function
	// Read image from file that already exists
	wolfImage, wolfImageErr := os.Open(importedImagePath) //example of image path "Source/wolf1.jpeg"
	if wolfImageErr != nil {
		// Handle error
	}
	defer wolfImage.Close()

	// directly decode image
	loadedWolfImage, loadedWolfImageErr := jpeg.Decode(wolfImage)
	if loadedWolfImageErr != nil {
		// Handle error
	}

	//determine image size
	imageRect := loadedWolfImage.Bounds()
	wolfImgWidth := imageRect.Dx()
	wolfImgHeight := imageRect.Dy()
	fmt.Print(wolfImgWidth)
	fmt.Print(" by ")
	fmt.Println(wolfImgHeight)
}

func generateWolfMeme(wolf *Wolf) { //void function 
	//apply text
	const fontSize = 48
	imagePath := "./wolfMeme.jpeg"

	m := gg.NewContext(wolfImgWidth, wolfImgHeight)
	m.DrawImage(loadedWolfImage, 0, 0)
	m.LoadFontFace("/Library/Fonts/Impact.ttf", fontSize)

	// Apply black stroke
	m.SetHexColor("#000")
	strokeSize := 6
	for dy := -strokeSize; dy <= strokeSize; dy++ {
		for dx := -strokeSize; dx <= strokeSize; dx++ {
			// give it rounded corners
			if dx*dx+dy*dy >= strokeSize*strokeSize {
				continue
			}
			x := float64(wolfImgWidth/2 + dx)
			y := float64(wolfImgHeight - fontSize + dy)
			m.DrawStringAnchored(wolf.wisdom, x, y, 0.5, 0.5)
		}
	}

	// Apply white fill
	m.SetHexColor("#FFF")
	m.DrawStringAnchored(wolf.wisdom, float64(wolfImgWidth)/2, float64(wolfImgHeight)-fontSize, 0.5, 0.5)

	//save image
	m.SavePNG(imagePath)
	fmt.Printf("Saved to %s\n", imagePath)
}

////////////////////////////////////////////////////////////
//MAIN

func main() {
	//SPECIFY WOLF NAME HERE AND DESIRED WISDOM
	var userWisdom = "Nevazhno kto silnee, vazhno kto nasral" //if you want to use default wisdom type "default"
	newWiseWolf := newWolf("Default Wolf", userWisdom)
	fmt.Println("Welcome to Wolf Wisdom Generator V0.0.1")
	fmt.Println("We created the default wolf with user-specified wisdom")
	fmt.Println("IF NO WISDOM PROVIDED WOLF SAYS DEFAULT WISDOM")
	fmt.Println(newWiseWolf.name)
	fmt.Println(newWiseWolf.wisdom)

	readAndDecodeImage(pathToWolfImage)

	generateWolfMeme(newWiseWolf)	
}

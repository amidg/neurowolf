package main //THIS IS TEST MAIN

import (
	"fmt"
	"log"

	//wolfTest "Wolf/Wolf"

	//required to read image from file
	"image"
	"image/jpeg"
	_ "image/png"
	"io/ioutil"
	"math/rand"
	"os"
	"time"

	"strings"

	"bufio"

	"github.com/fogleman/gg" //needed to draw text on image
	"github.com/golang/freetype/truetype"
	"golang.org/x/image/font/gofont/goregular"

	"C" // needed to run C++ wrapper
)

/////////////////////////////////////////////
//GLOBAL VARIABLES
var (
	pathToWolfImagesFolder  = "./ImgSource/"
	numberOfAvailableImages = 0
	wolfTemplateNames       [999]string //NO IDEA HOW MUCH RAM THIS TAKES, PROBABLY COUPLE MBs, specified maximum  number of images as long as there is enough RAM
	userWisdom              = "Wolf is stronger than lion but buys beer"
)

/////////////////////////////////////////////
//WILL BE REMOVED LATER INTO A SEPARATE FILE
//WISDOM STRUCT

//WOLF STRUCT
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
func readAndDecodeImage() (image.Image, int, int) { //returns regenerated jpegs and its sizes
	rand.Seed(time.Now().UnixNano())
	var imageChosen = rand.Intn(numberOfAvailableImages) //choose random image between 0 and max image
	var imagePath = "ImgSource/" + wolfTemplateNames[imageChosen]
	//fmt.Println(imagePath)

	// Read image from file that already exists
	wolfImage, wolfImageErr := os.Open(imagePath) //example of image path "Source/wolf1.jpeg"
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

	return loadedWolfImage, wolfImgWidth, wolfImgHeight
}

func generateWolfMeme(wolf *Wolf, imgWidth int, imgHeight int, loadedDecodedJPEG image.Image) { //void function with OS output
	//apply text
	const fontSize = 36
	imagePath := "./wolfMeme.jpeg"

	//set font face
	font, err := truetype.Parse(goregular.TTF)
	if err != nil {
		log.Fatal(err)
	}

	face := truetype.NewFace(font, &truetype.Options{Size: fontSize})

	m := gg.NewContext(imgWidth, imgHeight)
	m.DrawImage(loadedDecodedJPEG, 0, 0)
	//m.LoadFontFace("/Library/Fonts/Impact.ttf", fontSize)
	m.SetFontFace(face)

	// Apply black stroke
	m.SetHexColor("#000")
	strokeSize := 6
	for dy := -strokeSize; dy <= strokeSize; dy++ {
		for dx := -strokeSize; dx <= strokeSize; dx++ {
			// give it rounded corners
			if dx*dx+dy*dy >= strokeSize*strokeSize {
				continue
			}
			x := float64(imgWidth/2 + dx)
			y := float64(imgHeight - fontSize + dy)
			m.DrawStringAnchored(wolf.wisdom, x, y, 0.5, 0.5)
		}
	}

	// Apply white fill
	m.SetHexColor("#FFF")
	m.DrawStringAnchored(wolf.wisdom, float64(imgWidth)/2, float64(imgHeight)-fontSize, 0.5, 0.5)
	//func (dc *Context) DrawStringAnchored(s string, x, y, ax, ay float64)
	//DrawStringAnchored draws the specified text at the specified anchor point. The anchor point is x - w * ax, y - h * ay, where w, h is the size of the text. Use ax=0.5, ay=0.5 to center the text at the specified point.

	//save image
	m.SavePNG(imagePath)
	fmt.Printf("Saved to %s\n", imagePath)
}

func checkSourceWolfImages(pathToImages string) { //purely void function
	files, err := ioutil.ReadDir(pathToWolfImagesFolder)

	if err != nil {
		log.Fatal(err)
	}

	for iter, f := range files {
		//fmt.Println(f.Name()) //debug only
		wolfTemplateNames[iter] = f.Name()
		numberOfAvailableImages = numberOfAvailableImages + 1
		iter = iter + 1
	}

	fmt.Println(wolfTemplateNames)
}

func getManuallySpecifiedWisdom() string { //purely void function
	var receivedWisdom = "there is error in function, please, debug"
	//reader := bufio.NewReader(os.Stdin)
	fmt.Println("Ready to read user specified wisdom, enter 'default' for default wisdom")

	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("Enter custom wisdom for your wolf")
	fmt.Print("->")
	for scanner.Scan() {
		fmt.Println(scanner.Text())
		receivedWisdom = scanner.Text()
		receivedWisdom = "Не нужно менять себя ради кого-то важно кто насрал"

		if receivedWisdom != "there is error in function, please, debug" {
			break
		}
	}

	return receivedWisdom
}

//file reading functions for machine generated wisdom
func getNumberOfLinesInText(fileName string) int {
	// if len(os.Args) <= 1 {
	// 	fmt.Printf("USAGE : %s <target_filename> \n", os.Args[0])
	// 	os.Exit(0)
	// }

	// fileName := os.Args[1]

	fileBytes, err := ioutil.ReadFile(fileName)
	var numberOfLinesInText = 0

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	lines := strings.Split(string(fileBytes), "\n")

	// remove the last item from the lines slice
	// which is empty
	lines = lines[:len(lines)-1]

	// len() function will count the total number of lines
	fmt.Println(fileName, "has a total of", len(lines), "lines")
	for i, line := range lines {
		// i = i + 1 // uncomment to start from 1 instead of 0
		fmt.Println(i, line)
		numberOfLinesInText = numberOfLinesInText + 1
	}

	return numberOfLinesInText
}

func getMachineGeneratedWisdom() int { //string output of the machine specified wisdom
	var receivedWisdom = "there is error in function, please, debug"
	//reader := bufio.NewReader(os.Stdin)
	fmt.Println("Ready to read user specified wisdom, enter 'default' for default wisdom")

	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("Enter custom wisdom for your wolf")
	fmt.Print("->")
	for scanner.Scan() {
		fmt.Println(scanner.Text())
		receivedWisdom = scanner.Text()
		receivedWisdom = "Не нужно менять себя ради кого-то важно кто насрал"

		if receivedWisdom != "there is error in function, please, debug" {
			break
		}
	}

	return receivedWisdom
}

////////////////////////////////////////////////////////////
//MAIN

func main() {
	//SPECIFY WOLF NAME HERE AND DESIRED WISDOM

	userWisdom := getManuallySpecifiedWisdom() //get wisdom from the keyboard
	//userWisdom = getAutomaticallySpecifiedWisdom() //neural network wisdom
	fmt.Println(getMachineGeneratedWisdom)

	newWiseWolf := newWolf("Default Wolf", userWisdom)
	fmt.Println("Welcome to Neural Wolf Generator Rev 1.0")
	fmt.Println("We created the default wolf with user-specified wisdom")
	fmt.Println("IF NO WISDOM PROVIDED WOLF SAYS DEFAULT WISDOM")
	fmt.Println(newWiseWolf.name)
	fmt.Println(newWiseWolf.wisdom)

	//choose a template
	checkSourceWolfImages(pathToWolfImagesFolder)

	//generate image compatible with Golang
	loadedWolfImage, wolfImgWidth, wolfImgHeight := readAndDecodeImage() //takes global variable within the function

	//generate meme
	generateWolfMeme(newWiseWolf, wolfImgWidth, wolfImgHeight, loadedWolfImage)
}

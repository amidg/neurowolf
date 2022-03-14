package main

import (
	"fmt"
	"log"
	"os"
	"os/exec"
	"strconv"

	//"io/ioutil"

	//tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api"
)

//var TELEGRAM_BOT_TOKEN	= "";
var TELEGRAM_BOT_TOKEN = "" // wolf token must be passed as variable for github security
var TELEGRAM_CHAT_ID = ""   // chat id
var TRIGGER_GENERATION = false
var IMAGE_ID = ""

func execute_command(trigger bool, imgID string) {
	if trigger {
		app := "./wolfwisdomgenerator"

		//cmd := exec.Command(app, "--imageid", imgID, "--phrases 2")
		cmd := exec.Command(app, imgID)
		out, err := cmd.Output()

		if err != nil {
			fmt.Println(err.Error())
			return
		} else {
			fmt.Println(out)
		}

		cmd.Wait()
	}
}

var wolfKeyboard = tgbotapi.NewReplyKeyboard(
	tgbotapi.NewKeyboardButtonRow(
		tgbotapi.NewKeyboardButton("/quote"),
		tgbotapi.NewKeyboardButton("/help"),
	),
)

func main() {
	//TELEGRAM_BOT_TOKEN := os.Args[1]; // telegram bot token
	//TELEGRAM_CHAT_ID := os.Args[2]; // parse telegram chat token

	bot, err := tgbotapi.NewBotAPI(os.Getenv("TELEGRAM_WOLF_APITOKEN"))
	if err != nil {
		log.Panic(err)
	}

	bot.Debug = true

	log.Printf("Authorized on account %s", bot.Self.UserName)

	updateConfig := tgbotapi.NewUpdate(0)
	updateConfig.Timeout = 1

	updates, _ := bot.GetUpdatesChan(updateConfig)

	for update := range updates {
		// ================== loop to read chat updates ============== //

		if update.Message == nil { // ignore any non-Message updates
			continue
		}

		if !update.Message.IsCommand() { // ignore any non-command Messages
			continue
		}

		// Create a new MessageConfig. We don't have text yet,
		// so we leave it empty.
		msg := tgbotapi.NewMessage(update.Message.Chat.ID, "")

		msg.ReplyMarkup = wolfKeyboard

		// if we got message command
		switch update.Message.Command() {
		case "start":
			msg.Text = "Welcome to Нейроволк! \n /wolf -> say wolf quote \n /help -> show available commands"
		case "help":
			msg.Text = "I understand /wolf or /quote."
			msg.ReplyToMessageID = update.Message.MessageID
			bot.Send(msg)
		case "wolf":
			TRIGGER_GENERATION = true
			IMAGE_ID = strconv.Itoa(update.Message.MessageID)
		case "quote":
			TRIGGER_GENERATION = true
			IMAGE_ID = strconv.Itoa(update.Message.MessageID)
		default:
			msg.Text = "I understand /wolf or /quote"
			msg.ReplyToMessageID = update.Message.MessageID
			bot.Send(msg)
		}

		if TRIGGER_GENERATION {
			execute_command(TRIGGER_GENERATION, IMAGE_ID) // trigger compiled c++ program to execute the image generator

			msg.Text = "Wolf has spoken!"
			println("waiting for: wolfMeme" + IMAGE_ID + ".jpeg")
			msg := tgbotapi.NewPhotoUpload(update.Message.Chat.ID, "./GeneratedImages/wolfMeme"+IMAGE_ID+".jpeg")
			//msg.Caption = message.CommandArguments()
			msg.ReplyToMessageID = update.Message.MessageID
			bot.Send(msg)
			TRIGGER_GENERATION = false
		}

		if _, err := bot.Send(msg); err != nil {
			log.Panic(err)
		}

		// ============== infinite for loop =================== //
	}
}

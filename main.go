package main

import (
	"log"
	"os"
	"fmt"
	"os/exec"
	"io/ioutil"

	//tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api"
)

//var TELEGRAM_BOT_TOKEN	= "";
var TELEGRAM_BOT_TOKEN = ""; // wolf token must be passed as variable for github security
var TELEGRAM_CHAT_ID = ""; // chat id
var TRIGGER_GENERATION = false;
var IMAGE_ID = "";

func execute_command(trigger bool, imgID string) {
	if trigger {
		app := "./wolfwisdomgenerator "

		arg0 := imgID

		cmd := exec.Command(app, arg0)
		_, err := cmd.Output()

		if err != nil {
			fmt.Println(err.Error())
			return
		}
	}
}

func main() {
	//TELEGRAM_BOT_TOKEN := os.Args[1]; // telegram bot token
	//TELEGRAM_CHAT_ID := os.Args[2]; // parse telegram chat token

	bot, err := tgbotapi.NewBotAPI(os.Getenv("TELEGRAM__WOLF_APITOKEN"))
	if err != nil {
		log.Panic(err)
	}

	bot.Debug = true

	log.Printf("Authorized on account %s", bot.Self.UserName)

	updateConfig := tgbotapi.NewUpdate(0)
	updateConfig.Timeout = 10

	updates, _ := bot.GetUpdatesChan(updateConfig)

	for update := range updates {
		// ================== infinite loop ============== //
		if update.Message == nil { // ignore any non-Message updates
            continue
        }

        if !update.Message.IsCommand() { // ignore any non-command Messages
            continue
        }

		// Create a new MessageConfig. We don't have text yet,
        // so we leave it empty.
        msg := tgbotapi.NewMessage(update.Message.Chat.ID, "")

		// if we got message
		if update.Message != nil { // If we got a message
			log.Printf("[%s] %s", update.Message.From.UserName, update.Message.Text)

			// Extract the command from the Message.
			switch update.Message.Command() {
				case "help":
					msg.Text = "I understand /wolf or /say."
					msg.ReplyToMessageID = update.Message.MessageID
					bot.Send(msg)
				case "wolf":
					TRIGGER_GENERATION = true;
					IMAGE_ID = string(update.Message.MessageID);
				case "say":
					TRIGGER_GENERATION = true;
					IMAGE_ID = string(update.Message.MessageID);
				default:
					msg.Text = "I don't know that command"
					msg.ReplyToMessageID = update.Message.MessageID
					bot.Send(msg)
			}
		}
		
		if TRIGGER_GENERATION {
			execute_command(TRIGGER_GENERATION, IMAGE_ID); // trigger compiled c++ program to execute the image generator

			photoBytes, err := ioutil.ReadFile("./GeneratedImages/wolfMeme" + IMAGE_ID + ".jpeg")
			if err != nil {
				panic(err)
			}

			photoFileBytes := tgbotapi.FileBytes{Name:  "wolfMeme.jpg", Bytes: photoBytes}
			msg := tgbotapi.NewPhotoUpload(update.Message.Chat.ID, photoFileBytes);
			//msg.Caption = message.CommandArguments()
			msg.ReplyToMessageID = update.Message.MessageID
			bot.Send(msg);
		}

		if _, err := bot.Send(msg); err != nil {
			log.Panic(err)
		}

		// ============== infinite for loop =================== //
	}
}
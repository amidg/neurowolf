package main

import (
	"log"
	"os"
	"fmt"
	"os/exec"
	"string"

	tgbotapi "github.com/go-telegram-bot-api/telegram-bot-api/v5"
)

//var TELEGRAM_BOT_TOKEN	= "";
var TELEGRAM_BOT_TOKEN = "5154851264:AAFHRtrwyW0iuYsJ6tI8ag26VMp9HwW2Qgg"; // wolf token must be passed as variable for github security
var TELEGRAM_CHAT_ID = ""; // chat id
var TRIGGER_GENERATION = false;
var IMAGE_ID = "";

func execute_command(trigger bool, string imgID) {
	if trigger {
		app := "./wolfwisdomgenerator "

		arg0 := imgID

		cmd := exec.Command(app, arg0)
		stdout, err := cmd.Output()

		if err != nil {
			fmt.Println(err.Error())
			return
		}
	}
}

func main() {
	argsWithoutProg := os.Args[1:]
	TELEGRAM_CHAT_ID := os.Args[1]; // parse telegram chat token

	bot, err := tgbotapi.NewBotAPI(os.Getenv(TELEGRAM_BOT_TOKEN))
	if err != nil {
		log.Panic(err)
	}

	bot.Debug = true

	log.Printf("Authorized on account %s", bot.Self.UserName)

	u := tgbotapi.NewUpdate(0)
	u.Timeout = 60

	updates := bot.GetUpdatesChan(u)

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

		// photoBytes, err := ioutil.ReadFile("./GeneratedImages/wolfMeme.png")
		// if err != nil {
		// 	panic(err)
		// }
		// photoFileBytes := tgbotapi.FileBytes{
		// 	Name:  "picture",
		// 	Bytes: photoBytes,
		// }
		// chatID := 12345678
		// message, err := bot.Send(tgbotapi.NewPhotoUpload(int64(chatID), photoFileBytes))

		if _, err := bot.Send(msg); err != nil {
			log.Panic(err)
		}

		// ============== infinite for loop =================== //
	}
}
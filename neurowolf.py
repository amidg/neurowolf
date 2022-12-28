import logging
import os

# telegram bot stuff
from telegram import Update
from telegram.ext import ApplicationBuilder, ContextTypes, CommandHandler

# stable diffusion stuff
from torch import autocast
from diffusers import StableDiffusionPipeline

# opencv stuff
import numpy as np
import cv2

# basic logging
logging.basicConfig(
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    level=logging.INFO
)

# wolf meme class
class Wolf:
    def __init__(self, chat_id, message_id):
        self.chat_id = chat_id
        self.message_id = message_id
        self.image_path = "./result/" + self.chat_id + "_" + self.message_id + ".png"
        self.image_side_size = 512
        self.stable_diffusion_pipeline = StableDiffusionPipeline.from_pretrained(
            "CompVis/stable-diffusion-v1-4", 
            use_auth_token=True
        ).to("cuda")
        self.wolf_wisdom = ""

    # text generation function
    
    # stable diffusion
    def generate_stable_diffusion_image(self, prompt):
        with autocast("cuda"):
            image = self.stable_diffusion_pipeline(prompt)["sample"][0]  
        image.save(self.image_path)

    # OpenCV for text
    def put_text_on_image(self):
        # read image, all images are 512 x 512 because of how we generate them in stable diffusion
        img = cv2.imread(self.image_path, cv2.IMREAD_GRAYSCALE)

        # get text size from the wolf wisdom
        text_font = cv2.FONT_HERSHEY_DUPLEX
        text_font_scale = 1
        text_font_thickness = 4 # black background stroke is used for reference
        size, _ = cv2.getTextSize(self.wolf_wisdom, text_font, text_font_scale, text_font_thickness)
        width, height = size
        offset = 12

        # image size is hardcoded, so we can use that
        text_cursor = (self.image_side_size/2 - width/2, self.image_side_size - offset - height) # x, y

        # apply bottom text with stroke
        cv2.putText(img, self.wolf_wisdom,  # black text background
            text_cursor,            # bottom left corner of the image, 0, 0 is top right corner 
            text_font,              # text font
            text_font_scale,        # font scale
            (0, 0, 0),              # black stroke text
            text_font_thickness,    # thickness
            2)                      # line type

        cv2.putText(img, self.wolf_wisdom, # white text font
            text_cursor,            # bottom left corner of the image, 0, 0 is top right corner 
            text_font,              # text font
            text_font_scale,        # font scale
            (255, 255, 255),        # white text
            text_font_thickness/2,  # thickness
            2)                      # line type

        # output the image to overwriting it
        cv2.imwrite(self.image_path, img)


'''
    command to execute wolf meme generation
'''
async def get_wolf_meme(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await context.bot.send_message(chat_id=update.effective_chat.id, text="I'm a bot, please talk to me!")

# main function
if __name__ == '__main__':
    application = ApplicationBuilder().token(os.getenv('TELEGRAM_TOKEN')).build()
    
    # code that handles /fast_quote command that executes quote on standard image
    get_wolf_meme_handler = CommandHandler('wisdom', get_wolf_meme)
    application.add_handler(get_wolf_meme_handler)
    
    application.run_polling()
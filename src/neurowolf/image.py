from io import BytesIO
from PIL import Image, ImageDraw, ImageFont
from utils import get_image_list
import random

def create_image(phrases, image_stream: BytesIO):
    """
    Function to create image with text
    Picks random image from the content folder
    """
    # Get list of available images
    image_files = get_image_list()
    
    if not image_files:
        raise ValueError("No image files found in the specified directory.")
    
    # Choose a random image file
    img_path = random.choice(image_files)
    
    # Open the selected image as background
    background_img = Image.open(img_path).convert("RGB")
    
    # Create a blank image with the same size as the background image
    background_img = background_img.convert("RGB")
    final_img = Image.new("RGB", background_img.size, color=(30, 30, 30))
    # Paste the background image onto the final image
    final_img.paste(background_img)

    # draw text
    draw = ImageDraw.Draw(final_img)
    font = ImageFont.truetype("./content/Roboto-Regular.ttf", 48, encoding='UTF-8')
    
    # Split the phrases into top and bottom parts
    top_text = phrases[0]
    bottom_text = phrases[1]
    
    # Calculate text size to center them properly
    _, _, w1, h1 = draw.textbbox((0, 0), top_text, font=font)
    _, _, w2, h2 = draw.textbbox((0, 0), bottom_text, font=font)
    
    # Position for the top text (centered horizontally at the top of the image)
    top_position = ((final_img.width - w1) // 2, 50)
    # Position for the bottom text (centered horizontally at the bottom of the image)
    bottom_position = ((final_img.width - w2) // 2, final_img.height - h2 - 50)
    
    # Draw top and bottom texts
    draw.text(top_position, top_text, font=font, fill="black", stroke_width=3, stroke_fill="white")
    draw.text(bottom_position, bottom_text, font=font, fill="black", stroke_width=3, stroke_fill="white")
    
    # Save image to the provided stream
    final_img.save(image_stream, format="PNG")
    image_stream.seek(0)


def create_empty_image(text, image_stream: BytesIO):
    """
    Sample test function to create empty image with text
    """
    # Create an image with dark background
    img = Image.new("RGB", (500, 300), color=(30, 30, 30)) 
    draw = ImageDraw.Draw(img)

    try:
        # Load a font
        font = ImageFont.truetype("arial.ttf", 40)
    except IOError:
        # Fallback if font not found
        font = ImageFont.load_default()

    # add text
    text_position = (50, 120)
    text_color = (255, 255, 255)
    draw.text(text_position, text, font=font, fill=text_color)

    # save image
    img.save(image_stream, format="PNG")
    image_stream.seek(0);

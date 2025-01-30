from io import BytesIO
from PIL import Image, ImageDraw, ImageFont

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

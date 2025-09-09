FROM python:3.11-slim

WORKDIR /app
COPY requirements.txt .
RUN pip install -r requirements.txt
CMD ["python3", "src/neurowolf/main.py"]

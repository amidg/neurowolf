FROM ghcr.io/amidg/dev_base:latest AS base

# install go
WORKDIR /app
RUN rm *
RUN wget https://go.dev/dl/go1.23.4.linux-amd64.tar.gz && \
    rm -rf /usr/local/go && \
    tar -C /usr/local -xzf go1.23.4.linux-amd64.tar.gz && \
    rm *
RUN echo "export PATH=$PATH:/usr/local/go/bin" >> ~/.bashrc

# project entrypoint
COPY . .
RUN chmod +x ./run_telegram_bot
ENTRYPOINT ["./run_telegram_bot"]

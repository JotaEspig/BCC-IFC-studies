FROM golang:latest

WORKDIR /app

COPY . .

RUN go mod download

ENV PORT 8080
EXPOSE 8080

RUN go build -o myhtml .
CMD ["./myhtml"]

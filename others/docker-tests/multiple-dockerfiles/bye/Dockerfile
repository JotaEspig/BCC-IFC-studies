FROM golang:latest

WORKDIR /app

COPY . .

RUN go mod download

ENV PORT 8081
EXPOSE 8081

RUN go build -o bye .
CMD ["./bye"]

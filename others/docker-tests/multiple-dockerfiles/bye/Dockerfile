FROM golang:latest

WORKDIR /app

COPY . .

RUN go mod download

ENV PORT 8082
EXPOSE 8082

RUN go build -o bye .
CMD ["./bye"]

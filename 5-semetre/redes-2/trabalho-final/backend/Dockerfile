# Use the official Golang image
FROM golang:1.24-alpine

# Set working directory inside the container
WORKDIR /app

# Copy Go modules and download dependencies
COPY go.mod go.sum ./
RUN go mod download

# Copy source code
COPY . .

# Build the Go app
RUN go build -o server

# Expose the application port
EXPOSE 8080

# Run the application
CMD ["./server"]

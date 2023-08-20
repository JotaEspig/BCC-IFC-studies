cd bye
PORT=8082 go run . &
pid1=$!
cd ../myhtml
PORT=8080 go run . &
pid2=$!
cd ../api_gateway
PORT=8081 go run . &
pid3=$!

echo Ctrl-C to exit...
read -r -d '' _ </dev/tty

kill $pid1
kill $pid2
kill $pid3

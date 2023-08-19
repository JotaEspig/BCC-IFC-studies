cd bye
PORT=8081 go run . &
pid1=$!
cd ../myhtml/cmd
PORT=8080 go run . &
pid2=$!

echo Ctrl-C to exit...
read -r -d '' _ </dev/tty

kill $pid1
kill $pid2

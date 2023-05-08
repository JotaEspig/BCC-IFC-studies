if [ ! $# -eq 2 ] && [ ! $# -eq 3 ]; then
    echo "invalid amount of arguments"
    exit
fi

initials="JVE"
subject="Alg"
list_number=$1
exercises_amount=$2
extension=".c"
if [ ! -z $3 ]; then
    extension=$3
fi

if [ ${#list_number} -eq 1 ]; then
    dir="$initials-$subject-0$list_number"
else
    dir="$initials-$subject-$list_number"
fi

echo "Creating dir: $dir"
mkdir $dir

echo "Creating exercises..."
for i in $(seq 1 $exercises_amount)
do
    if [ ${#i} -eq 1 ]; then
        filename="$dir/$dir-Ex-0$i$extension"
    else
        filename="$dir/$dir-Ex-$i$extension"
    fi
    echo -ne "\r$filename"
    touch $filename
done

if [ "$extension" = ".c" ]; then
    echo -e "*\n!*.c\n!*.h\n!.gitignore" > $dir/.gitignore
fi

echo -e "\033[2K"
echo "done"

if [ ! $# -eq 2 ]; then
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

dir="$initials-$subject-$list_number"

mkdir $dir

for i in $(seq 1 $exercises_amount)
do
    if [ ${#i} -eq 1 ]; then
	filename="$dir/$dir-Ex-0$i$extension"
    else
        filename="$dir/$dir-Ex-$i$extension"
    fi
    touch $filename
done

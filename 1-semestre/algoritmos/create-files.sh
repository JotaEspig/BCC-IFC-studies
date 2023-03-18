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
    filename="$dir/$dir-Ex-$i$extension"
    touch $filename
done

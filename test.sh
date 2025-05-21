
radius=$1
diameter=$(echo "2*$radius " | bc)
area=$(echo "3.14*$radius*$radius" | bc)
echo "Diameter : $diameter "
echo "Area : $area"



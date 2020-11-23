ifconfig -a | grep ether | grep -v net | awk '{print $2}'

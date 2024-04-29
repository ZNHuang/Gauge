#!/bin/bash

# Get CPU usage per core using mpstat
cpu_usage=$(mpstat -P ALL 1 1 | tail -n +4 |head -n 16 | awk '{print $4}')

# Split the output into an array
cpu_cores=( ${cpu_usage// /} )

# Print header
# echo "CPU Usage per Core:"

# Loop through each core and print usage
for core in "${cpu_cores[@]}"; do
  echo -n "$core,"
done
echo ""

# Reset counter (optional)
i=0

#!/bin/bash
Date=$(date)
cd ~/408_cpp_impl || exit
git add . 
git commit -m "$Date"
git push


MULTIF=./multif
COURSE=./course

# multif test

echo "========== test: multif ============"

$MULTIF ; test $? -eq 0 && echo '[TEST 1] OK'
$MULTIF true ; test $? -eq 0 && echo '[TEST 2] OK'
$MULTIF false; test $? -eq 1 && echo '[TEST 3] OK'
$MULTIF true true false; test $? -eq 1 && echo '[TEST 4] OK'
$MULTIF false false; test $? -eq 1 && echo '[TEST 5] OK'
$MULTIF true true; test $? -eq 0 && echo '[TEST 6] OK'
$MULTIF true true true true; test $? -eq 0 && echo '[TEST 7] OK'


echo "========== test: course ============="
$COURSE

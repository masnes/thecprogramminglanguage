DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
llpp ${DIR}/C.pdf &>>${DIR}/errors.log &

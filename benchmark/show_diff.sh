awk '{
    RED="\033[31m"
    GREEN="\033[32m"
    YELLOW="\033[33m"
    RESET="\033[m"
    if( NR>1 )
    {
        diff = $2 / $6
        if ( diff > 20 ) { printf "%s[KO] ", RED }
        else { printf "%s[OK] ", GREEN }
        printf "%s%6.2fx\033[m :\033[33m %s%s\n", \
                RESET,($2 / $6), COLOR, $1
    }
}' benchmark_diff.log

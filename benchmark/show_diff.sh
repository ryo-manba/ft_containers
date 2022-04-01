awk '{
    RED="\033[31m"
    GREEN="\033[32m"
    YELLOW="\033[33m"
    RESET="\033[m"

    if( $2 != "BENCHMARK" )
    {
        diff = 0
        ans = "OK"
        color = GREEN
        if ( $4 == "|" )
        {
            diff = $2 / $6
            if ( diff > 20 )
            {
                ans = "KO"
                color = RED
            }
        }
        printf "%s[%s] ",color, ans
        printf "%s%6.2fx\033[m : %s %s\n", RESET, diff, YELLOW, $1
    }
}' benchmark_diff.log

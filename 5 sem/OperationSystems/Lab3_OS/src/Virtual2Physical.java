public class Virtual2Physical
{
    public static int pageNum ( long memAddr , int numPages , long block )
    {
        for (int i = 0; i <= numPages; i++)
        {
            long low = block * i;
            long high = block * ( i + 1 );
            if ( low <= memAddr && memAddr < high )
            {
                return i;
            }
        }
        return -1;
    }
}
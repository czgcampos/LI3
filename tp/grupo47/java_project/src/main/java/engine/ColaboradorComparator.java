package engine;

import java.util.Comparator;
import java.io.Serializable;

public class ColaboradorComparator implements Comparator<Colaborador>,Serializable
{
    public int compare(Colaborador c1, Colaborador c2)
    {
        int contribuicoes1=c1.getContribuicoes();
        int contribuicoes2=c2.getContribuicoes();
        long id1=c1.getColaboradorId();
        long id2=c2.getColaboradorId();

        if(contribuicoes1>contribuicoes2)
        {
            return -1;
        }
        else if(contribuicoes1<contribuicoes2)
        {
            return 1;
        }
        else
        {
            if(id1<id2)
                return 1;
            else if(id1>id2)
                return -1;
            else
                return 0;
        }
    }
}
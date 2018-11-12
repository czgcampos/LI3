import java.io.Serializable;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class Artigos implements Serializable
{
    private List<Artigo> artigos;

    public Artigos()
    {
        this.artigos=new ArrayList<Artigo>();
    }

    public Artigos(List<Artigo> artigos)
    {
        this.artigos=new ArrayList<Artigo>(artigos);
    }

    public Artigos(Artigos a2)
    {
        this.artigos=a2.getArtigos();
    }
    
    public List<Artigo> getArtigos()
    {
        return this.artigos.stream().map(Artigo::clone).collect(Collectors.toList());
    }
    
    public long contaRep()
    {
        long res=0L;
        int i;
        for(i=0;i<this.artigos.size();i++)
        {
            if(i!=this.artigos.size()-1 && this.artigos.get(i).getRevisao().getRevisaoId()==this.artigos.get(i+1).getRevisao().getRevisaoId())
                res++;
        }
        return res;
    }

    public void setArtigos(List<Artigo> as)
    {
        this.artigos.clear();
        this.artigos=as.stream().map(Artigo::clone).collect(Collectors.toList());
    }

    public Artigos clone()
    {
        return new Artigos(this);
    }
    
    public boolean equals(Object o)
    {
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        else
        {
            Artigos as = (Artigos) o;
            return (this.artigos.equals(as.getArtigos()));
        }
    }
    
    public String toString()
    {
        StringBuilder s = new StringBuilder();
        s.append("Artigos\n");
        s.append(this.artigos+"\n");
        return s.toString();
    }
}
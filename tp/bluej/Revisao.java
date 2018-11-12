import java.io.Serializable;

public class Revisao implements Serializable
{
    private long id;
    private String data;
    private long nbytes;
    private long npalavras;

    public Revisao()
    {
        this.id=0L;
        this.data="";
        this.nbytes=0L;
        this.npalavras=0L;
    }

    public Revisao(long idRev, String data, long nbytes, long npalavras)
    {
        this.id=idRev;
        this.data=data;
        this.nbytes=nbytes;
        this.npalavras=npalavras;
    }

    public Revisao(Revisao r2)
    {
        this.id=r2.getRevisaoId();
        this.data=r2.getData();
        this.nbytes=r2.getNbytes();
        this.npalavras=r2.getNpalavras();
    }

    public long getRevisaoId()
    {
        return this.id;
    }

    public String getData()
    {
        return this.data;
    }

    public long getNbytes()
    {
        return this.nbytes;
    }

    public long getNpalavras()
    {
        return this.npalavras;
    }

    public void setRevisaoId(long id)
    {
        if(id>0L)
            this.id=id;
    }

    public void setData(String data)
    {
        this.data=data;
    }

    public void setNbytes(long nbytes)
    {
        if(nbytes>0L)
            this.nbytes=nbytes;
    }

    public void setNpalavras(long npalavras)
    {
        if(npalavras>0L)
            this.npalavras=npalavras;
    }

    public Revisao clone()
    {
        return new Revisao(this);
    }
    
    public boolean equals(Object o)
    {
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        else
        {
            Revisao r = (Revisao) o;
            return (this.id==r.getRevisaoId() &&
            		this.data.equals(r.getData()) &&
            		this.nbytes==r.getNbytes() &&
            		this.npalavras==r.getNpalavras());
        }
    }
    
    public String toString()
    {
        StringBuilder s = new StringBuilder();
        s.append("Revisao\n");
        s.append("Id: ");
        s.append(this.id+"\n");
        s.append("Data: ");
        s.append(this.data+"\n");
        s.append("Numero de bytes: ");
        s.append(this.nbytes+"\n");
        s.append("Numero de palavras: ");
        s.append(this.npalavras+"\n");
        return s.toString();
    }
}
package engine;

import java.io.Serializable;

public class Artigo implements Serializable
{
	private String titulo;
	private Revisao revisao;

	public Artigo()
	{
		this.titulo="";
		this.revisao=new Revisao();
	}

	public Artigo(String titulo, long idRev, String data, long nbytes, long npalavras)
	{
		this.titulo=titulo;
		this.revisao=new Revisao(idRev,data,nbytes,npalavras);
	}

	public Artigo(Artigo a2)
	{
		this.titulo=a2.getTitulo();
		this.revisao=a2.getRevisao();
	}

	public String getTitulo()
	{
		return this.titulo;
	}

	public Revisao getRevisao()
	{
		return this.revisao;
	}

	public void setTitulo(String titulo)
	{
		if(titulo.equals(""))
			this.titulo=titulo;
	}

	public void setRivsao(long idRev, String data, long nbytes, long npalavras)
	{
		this.revisao=new Revisao(idRev,data,nbytes,npalavras);
	}

	public Artigo clone()
    {
        return new Artigo(this);
    }
    
    public boolean equals(Object o)
    {
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        else
        {
            Artigo a = (Artigo) o;
            return (this.titulo.equals(a.getTitulo()) && 
            		this.revisao.equals(a.getRevisao()));
        }
    }
    
    public String toString()
    {
        StringBuilder s = new StringBuilder();
        s.append("Artigo\n");
        s.append("Titulo: ");
        s.append(this.titulo+"\n");
        s.append("Revisao: ");
        s.append(this.revisao+"\n");
        return s.toString();
    }
}
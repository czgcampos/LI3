package engine;

import java.io.Serializable;
import java.util.List;
import java.util.ArrayList;

public class Colaborador implements Serializable
{
	private long id;
	private String nome;
	private int contribuicoes;
	private List<Long> ids;

	public Colaborador()
	{
		this.id=0L;
		this.nome="";
		this.contribuicoes=0;
		this.ids=new ArrayList<Long>();
	}
	
	public Colaborador(long id, String nome)
	{
	    this.id=id;
		this.nome=nome;
		this.contribuicoes=0;
		this.ids=new ArrayList<Long>();
	}

	public Colaborador(long id, String nome, int contribuicoes, List<Long> ids)
	{
		this.id=id;
		this.nome=nome;
		this.contribuicoes=contribuicoes;
		this.ids=new ArrayList<Long>(ids);
	}

	public Colaborador(Colaborador c2)
	{
		this.id=c2.getColaboradorId();
		this.nome=c2.getNome();
		this.contribuicoes=c2.getContribuicoes();
		this.ids=c2.getIds();
	}

	public long getColaboradorId()
	{
		return this.id;
	}

	public String getNome()
	{
		return this.nome;
	}

	public int getContribuicoes()
	{
		return this.contribuicoes;
	}

	public List<Long> getIds()
	{
		return this.ids;
	}

	public void setColaboradorId(long id)
	{
		if(id>0L)
			this.id=id;
	}

	public void setNome(String nome)
	{
		if(nome.equals(""))
			this.nome=nome;
	}

	public void setContribuicoes(int contribuicoes)
	{
		if(contribuicoes>0)
			this.contribuicoes=contribuicoes;
	}

	public void setIds(List<Long> ids)
    {
        this.ids=new ArrayList<Long>(ids);
    }

	public Colaborador clone()
    {
        return new Colaborador(this);
    }
    
    public boolean equals(Object o)
    {
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;
        else
        {
            Colaborador c = (Colaborador) o;
            return (this.id==c.getColaboradorId() &&
            		this.nome.equals(c.getNome()) &&
            		this.contribuicoes==c.getContribuicoes() &&
            		this.ids.equals(c.getIds()));
        }
    }
    
    public String toString()
    {
        StringBuilder s = new StringBuilder();
        s.append("Colaborador\n");
        s.append("Id: ");
        s.append(this.id+"\n");
        s.append("Nome: ");
        s.append(this.nome+"\n");
        s.append("Contribuicoes: ");
        s.append(this.contribuicoes+"\n");
        s.append("Lista de Ids de revisões que escreveu: ");
        s.append(this.ids+"\n");
        return s.toString();
    }
}
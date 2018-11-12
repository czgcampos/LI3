import java.util.*;
import static java.util.Comparator.*;
import static java.util.stream.Collectors.toMap;
import java.io.*;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamReader;
import java.lang.String;
import java.util.regex.*;

public class QueryEngineImpl implements Serializable 
{
    private Map<Long, Artigos> snaps;
    private long numeroArtigos;
    private long numeroArtigosUnicos;
    private long numeroRevisoes;
    private Map<Long,Colaborador> colaboradores1;
    private Set<Colaborador> colaboradores2;
    
    public void adicionaColaborador(long idColab, long idRev, String nome)
    {
        int aux=0;
        List<Long> lista=new ArrayList<>();
        if(this.colaboradores1.containsKey(idColab) && idColab!=0)
        {
            lista=this.colaboradores1.get(idColab).getIds();
            aux=this.colaboradores1.get(idColab).getContribuicoes();
            if(!lista.contains(idRev))
            {
                lista.add(idRev);
                aux++;
            }
            this.colaboradores1.get(idColab).setContribuicoes(aux);
            this.colaboradores1.get(idColab).setIds(lista);
        }
        else if(idColab!=0)
        {
            lista.add(idRev);
            Colaborador c=new Colaborador(idColab,nome,1,lista);
            this.colaboradores1.put(idColab,c);
        }
    }
    
    public void adicionarArtigo(Artigo art, long idArt)
    {
        List<Artigo> lista=new ArrayList<>();
        if(this.snaps.containsKey(idArt))
        {
            lista=this.snaps.get(idArt).getArtigos();
            lista.add(0,art);
            this.snaps.get(idArt).setArtigos(lista);
        }
        else
        {
            lista.add(art);
            Artigos arts=new Artigos(lista);
            this.snaps.put(idArt,arts);
        }
    }

    public void init()
    {
        this.snaps=new HashMap<>();
        this.numeroArtigos=0L;
        this.numeroArtigosUnicos=0L;
        this.numeroRevisoes=0L;
        this.colaboradores1=new HashMap<>();
        this.colaboradores2=new TreeSet<Colaborador>(new ColaboradorComparator());
    }

    public void lerFicheiro(String nomeFicheiro)
    {
        try
        {
            XMLInputFactory input = XMLInputFactory.newFactory();
            XMLStreamReader stream = input.createXMLStreamReader(new FileInputStream(nomeFicheiro));
            int tipoEvento;
            String titulo="", data="", nome="", texto="";
            long idArt=0L,idRev=0L,idColab=0L,nbytes=0L,npalavras=0L;
            Artigo art=new Artigo();
            Colaborador col=new Colaborador();
            for(;stream.hasNext();stream.next())
            {
                tipoEvento=stream.getEventType();
                if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("page"))
                {
                    for(;stream.hasNext();stream.next())
                    {
                        tipoEvento=stream.getEventType();
                        if(tipoEvento==XMLStreamReader.END_ELEMENT && stream.getLocalName().equals("page"))
                            break;
                        if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("title"))
                        {
                            stream.next();
                            tipoEvento=stream.getEventType();
                            if(tipoEvento==XMLStreamReader.CHARACTERS)
                                titulo=stream.getText();
                        }
                        if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("id"))
                        {
                            stream.next();
                            tipoEvento=stream.getEventType();
                            if(tipoEvento==XMLStreamReader.CHARACTERS)
                                idArt=Integer.parseInt(stream.getText());
                        }
                        if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("revision"))
                        {
                            for(;stream.hasNext();stream.next())
                            {
                                tipoEvento=stream.getEventType();
                                if(tipoEvento==XMLStreamReader.END_ELEMENT && stream.getLocalName().equals("revision"))
                                    break;
                                if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("id"))
                                {
                                    stream.next();
                                    tipoEvento=stream.getEventType();
                                    if(tipoEvento==XMLStreamReader.CHARACTERS)
                                        idRev=Integer.parseInt(stream.getText());
                                }
                                if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("timestamp"))
                                {
                                    stream.next();
                                    tipoEvento=stream.getEventType();
                                    if(tipoEvento==XMLStreamReader.CHARACTERS)
                                        data=stream.getText();
                                }
                                if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("text"))
                                {
                                    for(;stream.hasNext();stream.next())
                                    {
                                        tipoEvento=stream.getEventType();
                                        if(tipoEvento==XMLStreamReader.END_ELEMENT && stream.getLocalName().equals("text"))
                                            break;
                                        if(tipoEvento==XMLStreamReader.CHARACTERS)
                                        {
                                            nbytes+=stream.getText().getBytes("UTF-8").length;
                                            String trim=stream.getText().trim();
                                            if(trim.isEmpty())
                                                npalavras+=0L;
                                            else
                                                npalavras+=trim.replace("\n"," ").split("\\s+").length;
                                        }
                                    }
                                }
                                if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("contributor"))
                                {
                                    for(;stream.hasNext();stream.next())
                                    {
                                        tipoEvento=stream.getEventType();
                                        if(tipoEvento==XMLStreamReader.END_ELEMENT && stream.getLocalName().equals("contributor"))
                                            break;
                                        if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("username"))
                                        {
                                            stream.next();
                                            tipoEvento=stream.getEventType();
                                            if(tipoEvento==XMLStreamReader.CHARACTERS)
                                                nome=stream.getText();
                                        }
                                        if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("id"))
                                        {
                                            stream.next();
                                            tipoEvento=stream.getEventType();
                                            if(tipoEvento==XMLStreamReader.CHARACTERS)
                                                idColab=Integer.parseInt(stream.getText());
                                        }
                                        if(tipoEvento==XMLStreamReader.START_ELEMENT && stream.getLocalName().equals("ip"))
                                        {
                                            nome="";
                                            idColab=0L;
                                        }
                                    }
                                }
                            }
                            adicionaColaborador(idColab,idRev,nome);
                        }
                    }
                    art=new Artigo(titulo,idRev,data,nbytes,npalavras);
                    adicionarArtigo(art,idArt);
                    nbytes=0L;npalavras=0L;
                }
            }
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }
    }
    
    public void load(int nsnaps, ArrayList<String> snaps_paths)
    {
        for(String nomeDoc: snaps_paths)
            lerFicheiro(nomeDoc);
        this.numeroArtigosUnicos=snaps.size();
        long resultado=0L;
        for(Map.Entry<Long,Artigos> a : this.snaps.entrySet())
            resultado+=a.getValue().getArtigos().size();
        this.numeroArtigos=resultado;
        for(Map.Entry<Long,Artigos> a : this.snaps.entrySet())
            resultado-=a.getValue().contaRep();
        this.numeroRevisoes=resultado;
        List<Colaborador> colaboradoresAux=new ArrayList<>();
        for(Map.Entry<Long,Colaborador> c : this.colaboradores1.entrySet())
            colaboradoresAux.add(c.getValue());
        this.colaboradores2.addAll(colaboradoresAux);
    }

    public long all_articles()
    {
        return this.numeroArtigos;
    }

    public long unique_articles()
    {
        return this.numeroArtigosUnicos;
    }

    public long all_revisions()
    {
        return this.numeroRevisoes;
    }

    public ArrayList<Long> top_10_contributors()
    {
        ArrayList<Long> resultado=new ArrayList<Long>(10);
        Iterator<Colaborador> it = this.colaboradores2.iterator();
        int i;
        for(i=0;it.hasNext() && i<10;i++)
            resultado.add(it.next().getColaboradorId());
        return resultado;
    }

    public String contributor_name(long contributor_id)
    {
        if(this.colaboradores1.containsKey(contributor_id))
            return this.colaboradores1.get(contributor_id).getNome();
        else
            return null;
    }

    public ArrayList<Long> top_20_largest_articles()
    {
        ArrayList<Long> resultado=new ArrayList<>(20);
        ArrayList<Long> aux=new ArrayList<>(20);
        int i;
        for(i=0;i<20;i++)
        {
            resultado.add(i,0L);
            aux.add(i,0L);
        }
        long nb=0L;
        long id=0L; 
        List<Artigo> arts=new ArrayList<>();
        for(Map.Entry<Long,Artigos> a : this.snaps.entrySet())
        {
            id=a.getKey();
            arts=a.getValue().getArtigos();
            for(Artigo art: arts)
                if(art.getRevisao().getNbytes()>nb)
                    nb=art.getRevisao().getNbytes();
            for(i=0;i<20;i++)
                if(aux.get(i)<nb || (aux.get(i)==nb && resultado.get(i)>id))
                {
                    aux.add(i,nb);
                    resultado.add(i,id);
                    break;
                }
            nb=0;
        }
        return new ArrayList<Long>(resultado.subList(0,20));
    }

    public String article_title(long article_id)
    {
        if(this.snaps.containsKey(article_id))
            return this.snaps.get(article_id).getArtigos().get(0).getTitulo();
        else
            return null;
    }

    public ArrayList<Long> top_N_articles_with_more_words(int n)
    {
        ArrayList<Long> resultado=new ArrayList<>(n);
        ArrayList<Long> aux=new ArrayList<>(n);
        int i;
        for(i=0;i<n;i++)
        {
            resultado.add(i,0L);
            aux.add(i,0L);
        }
        long np=0L;
        long id=0L; 
        List<Artigo> arts=new ArrayList<>();
        for(Map.Entry<Long,Artigos> a : this.snaps.entrySet())
        {
            id=a.getKey();
            arts=a.getValue().getArtigos();
            for(Artigo art: arts)
            {
                if(art.getRevisao().getNpalavras()>np)
                    np=art.getRevisao().getNpalavras(); 
            }
            for(i=0;i<n;i++)
                if(aux.get(i)<np || (aux.get(i)==np && resultado.get(i)>id))
                {
                    aux.add(i,np);
                    resultado.add(i,id);
                    break;
                }
            np=0;
        }
        return new ArrayList<Long>(resultado.subList(0,n));
    }

    public ArrayList<String> titles_with_prefix(String prefix)
    {
        ArrayList<String> resultado=new ArrayList<>();
        String aux="";
        for(Map.Entry<Long,Artigos> a : this.snaps.entrySet())
        {
            aux=a.getValue().getArtigos().get(0).getTitulo();
            if(aux.startsWith(prefix))
                resultado.add(aux);
        }
        resultado.sort(naturalOrder());
        return resultado;
    }

    public String article_timestamp(long article_id, long revision_id)
    {
        if(this.snaps.containsKey(article_id))
        {
            List<Artigo> arts=this.snaps.get(article_id).getArtigos();
            for(Artigo artigo : arts)
                if(artigo.getRevisao().getRevisaoId()==revision_id)
                    return artigo.getRevisao().getData();
        }
        return null;
    }

    public void clean()
    {
        this.snaps.clear();
        this.numeroArtigos=0L;
        this.numeroArtigosUnicos=0L;
        this.numeroRevisoes=0L;
        this.colaboradores1.clear();
        this.colaboradores2.clear();
    }
}
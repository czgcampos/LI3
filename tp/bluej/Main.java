import java.util.List;
import java.util.ArrayList;

public class Main extends QueryEngineImpl
{
    public void main()
    {
        int n=3;
        String snap1="snapshot_dec16";
        String snap2="snapshot_jan17";
        String snap3="snapshot_fev17";
        ArrayList lista = new ArrayList<>();
        lista.add(0,snap3);
        lista.add(0,snap2);
        lista.add(0,snap1);
        
        init();
        
        load(n,lista);
        
        long res = unique_articles();
        System.out.println(res);
        
        res=all_articles();
        System.out.println(res);
        
        res=all_revisions();
        System.out.println(res);
        
        ArrayList<Long> resultado=new ArrayList<>();
        resultado=top_10_contributors();
        System.out.println(resultado);
        
        snap1=contributor_name(28903366);
        System.out.println(snap1);
        
        snap1=contributor_name(194203);
        System.out.println(snap1);
        
        snap1=contributor_name(1000);
        System.out.println(snap1);
        
        resultado=top_20_largest_articles();
        System.out.println(resultado);
        
        snap1=article_title(15910);
        System.out.println(snap1);
        
        resultado=top_N_articles_with_more_words(30);
        System.out.println(resultado);
        
        snap1=article_title(25507);
        System.out.println(snap1);
        
        snap1=article_title(1111);
        System.out.println(snap1);
        
        lista=titles_with_prefix("Anax");
        System.out.println(lista);
        
        snap1=article_timestamp(12,763082287);
        System.out.println(snap1);
        
        snap1=article_timestamp(12,755779730);
        System.out.println(snap1);
        
        snap1=article_timestamp(12,4479730);
        System.out.println(snap1);
    }
}

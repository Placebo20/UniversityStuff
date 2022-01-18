package newspaper;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class Newspaper {

    ArrayList<Category> categories = new ArrayList<>();
    ArrayList<News> news = new ArrayList<>();

    public static void saveToFile() throws ParserConfigurationException, TransformerException {
        DocumentBuilderFactory dbf = null;
        DocumentBuilder db = null;
        Document doc = null;
        dbf = DocumentBuilderFactory.newInstance();
        db = dbf.newDocumentBuilder();
        doc = db.newDocument();

        Element root = doc.createElement("newspaper");
        doc.appendChild(root);

        Element category1 = doc.createElement("category");
        category1.setAttribute("id","1");
        category1.setAttribute("name", "Science");
        root.appendChild(category1);

        Element category2 = doc.createElement("category");
        category2.setAttribute("id","2");
        category2.setAttribute("name", "Science");
        root.appendChild(category2);

        Element news1 = doc.createElement("news");
        news1.setAttribute("id","1");
        news1.setAttribute("name", "Why Greenpeace is dropping huge boulders into the sea");
        category1.appendChild(news1);

        Element news2 = doc.createElement("news");
        news2.setAttribute("id", "2");
        news2.setAttribute("name", "Nuclear fusion reactor experiment to produce clean energy!");
        category1.appendChild(news2);

        Element news3 = doc.createElement("news");
        news3.setAttribute("id","3");
        news3.setAttribute("name", "Life at sea by world's largest offshore wind farm in North Sea");
        category2.appendChild(news3);


        Source domSource = new DOMSource(doc);
        Result fileResult = new StreamResult(new File("D:\\PROJECTS\\University-VSem\\DistributedProgramming\\Lab2.1_DP\\src\\main\\resources\\out.xml"));
        TransformerFactory factory = TransformerFactory.newInstance();
        Transformer transformer = factory.newTransformer();
        transformer.setOutputProperty(OutputKeys.ENCODING,"WINDOWS-1251");
        transformer.transform(domSource, fileResult);
    }

    public void readFromFile(String filename) {

    }

    public void addCategory(int id, String name) throws Exception {
        for (Category category : categories) {
            if (category.getId() == id) throw new Exception("There is already an category with such id");
        }
        categories.add(new Category(id, name));
    }

    public Category getCategory(int id) throws Exception {
        for (Category category : categories) {
            if (category.getId() == id) return category;
        }
        throw new Exception("No category with such id");
    }

    public Category getCategoryInd(int id) throws Exception {
        if (id < categories.size()) return categories.get(id);
        else throw new Exception("Out of bounds!");
    }

    public int countCategories() {
        return categories.size();
    }

    public void deleteCategory(int id) throws Exception {
        boolean found = false;
        for (Category category : categories) {
            if (category.getId() == id) {
                categories.remove(category);
                found = true;
            }
        }
        if (!found) throw new Exception("Country with id " + id + " not found");
        for (News article : news) {
            if (article.getCategoryId() == id) news.remove(article);
        }
    }

    public void addArticle (int id, String name, int categoryId) throws Exception {
        for (News article : news) {
            if (article.getId() == id) throw new Exception("News with such id already exists");
        }
        boolean categoryExists = false;
        for (Category category : categories) {
            if (category.getId() == categoryId) {
                categoryExists = true;
            }
        }
        if(!categoryExists) throw  new Exception("NO such category!");
        news.add(new News(id,categoryId,name));
    }

    public static void main(String[] args) throws SAXException, TransformerException, ParserConfigurationException {

        saveToFile();

        DocumentBuilderFactory dbf = null;
        DocumentBuilder db = null;

        try {
            dbf = DocumentBuilderFactory.newInstance();

            SchemaFactory sf = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
            Schema s = sf.newSchema(new File("D:\\PROJECTS\\University-VSem\\DistributedProgramming\\Lab2.1_DP\\src\\main\\resources\\newspaper.xsd"));

            dbf.setValidating(false);
            dbf.setSchema(s);

            db = dbf.newDocumentBuilder();
            db.setErrorHandler(new SimpleErrorHandler());
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        }

        Document doc = null;
        try {
            doc = db.parse(new File("D:\\PROJECTS\\University-VSem\\DistributedProgramming\\Lab2.1_DP\\src\\main\\resources\\newspaper.xml"));
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        Element root = doc.getDocumentElement();
        if(root.getTagName().equals("newspaper")){
            NodeList listCategories = root.getElementsByTagName("category");
            for (int i = 0; i < listCategories.getLength(); i++) {
                Element category = (Element)listCategories.item(i);
                int categoryId = Integer.parseInt(category.getAttribute("id"));
                String categoryName = category.getAttribute("name");
                System.out.println("Category: " + categoryName + " (" + categoryId + ")");
                NodeList listNews = category.getElementsByTagName("news");
                for (int j = 0; j < listNews.getLength(); j++) {
                    Element news = (Element)listNews.item(j);
                    int newsId = Integer.parseInt(news.getAttribute("id"));
                    String newsName = news.getAttribute("name");
                    System.out.println("       " + newsName + " (" + newsId + ")");
                }
            }
        }
    }
}

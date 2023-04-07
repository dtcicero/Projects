import java.util.ArrayList;

public class Main {
	public static void main(String[] args) {
		//User declarations
		User user1 = new User("Arie");
		User user2 = new User("Daniel");
		User user3 = new User("Bob");
		User user4 = new User("Joe");
		User user5 = new User("Billy");
		
		//BackgroundImage declarations
		BackgroundImage image1 = new BackgroundImage("File1", "Class", "This is a class");
		BackgroundImage image2 = new BackgroundImage("File2", "Professor", "This is a professor");
		BackgroundImage image3 = new BackgroundImage("File3", "Student", "This is a student");
		BackgroundImage image4 = new BackgroundImage("File4", "Teacher", "This is a teacher");
		
		//Meme declarations
		Meme meme1 = new Meme(image1, "caption1", user1);
		Meme meme2 = new Meme(image2, "caption2", user2);
		Meme meme3 = new Meme(image3, "caption3", user3);
		Meme meme4 = new Meme(image4, "caption4", user4);
		
		ArrayList<Meme> memes = new ArrayList<Meme>();
		memes.add(meme1);
		memes.add(meme2);
		memes.add(meme3);
		
		//Feed Declarations
		Feed feed1 = new Feed();
		feed1.setMemes(memes);
		
		//Rating declarations
		Rating rating1 = new Rating(user1, 1);
		Rating rating2 = new Rating(user1, -5);
		Rating rating3 = new Rating(user2, 1);
		Rating rating4 = new Rating(user2, -1);
		
		//Printing each object
		System.out.println("User1 Print: " + user1);
		System.out.println("User2 Print: " + user2);
		System.out.println("Image1 Print: " + image1);
		System.out.println("Image2 Print: " + image2);
		System.out.println("Meme1 Print: " + meme1);
		System.out.println("Meme2 Print: " + meme2);
		System.out.println("Rating4 Print: " + rating4);
		System.out.println("Rating2 Print: " + rating2 + "\n");
		
		//Memes Methods
		meme1.addRating(rating1);
		meme1.addRating(rating2);
		meme1.addRating(rating3);
		meme1.addRating(rating4);
		System.out.println("Meme 1 COR: " + meme1.calculateOverallRating());
		meme1.addRating(new Rating(user3, -1));
		System.out.println("Meme 1 COR: " + meme1.calculateOverallRating());
		System.out.println("Meme1 SCVA (Set to That): " + meme1.setCaptionVerticalAlign("That") + " " +
							meme1.getCaptionVerticalAlign());
		System.out.println("Meme1 SCVA: " + meme1.setCaptionVerticalAlign("top") + " " + 
							meme1.getCaptionVerticalAlign());
		
		//Rating Methods
		System.out.println("Rating2 SS: " + rating2.setScore(-1) + " " + rating2.getScore());
		System.out.println("Rating4 SS (Set to 6): " + rating2.setScore(6) + " " + rating2.getScore());

		//Feed Methods
		System.out.println("User 1 GetNewMeme (x4): " + feed1.getNewMeme(user1) + "\n" + 
							feed1.getNewMeme(user1) + "\n" + feed1.getNewMeme(user1) + "\n" + 
							feed1.getNewMeme(user1));
		
		//User Methods
		user2.rateMeme(meme3, 1);
		user3.rateMeme(meme3, -1);
		user3.rateNextMemeFromFeed(feed1, 1);
		user3.rateNextMemeFromFeed(feed1, -1);
		
		user4.createMeme(image1, "Test Caption1");
		user4.createMeme(image2, "Test Caption2");
		
		System.out.println("Delete Meme Sucess: " + user4.deleteMeme(new Meme(image1, "Test Caption1", user4)));
		user4.shareMeme(new Meme(image2, "Test Caption2", user4), feed1);
		System.out.println("Delete Meme Fail: " + user4.deleteMeme(new Meme(image2, "Test Caption2", user4)));
		user3.shareMeme(meme2, feed1);
		
		user5.createMeme(image3, "Caption5");
		user5.createMeme(image4, "Caption6");
		for (Meme meme : user5.getMemesCreated()) {
			rating3.setScore((int)(Math.random() * 3) + 1);
			meme.addRating(rating3);
			meme.addRating(rating1);
		}
		System.out.println("User5 CalcRep: " + user5.calculateReputation());
		for (Meme meme : user5.getMemesCreated()) {
			rating3.setScore((int)(Math.random() * 3) + 1);
			meme.addRating(rating3);
			meme.addRating(rating1);
		}
		System.out.println("User5 CalcRep: " + user5.calculateReputation());
		
		
		//Equals Tests
		System.out.println("\nEquals Tests: ");
		image3 = image4;
		meme3 = meme4;
		user4 = user5;
		rating3 = rating4;
		System.out.println("Image Equals (False): " + image1.equals(image2));
		System.out.println("Image Equals (True)" + image3.equals(image4));
		System.out.println("Meme Equals (False): " + meme1.equals(meme2));
		System.out.println("Meme Equals (True): " + meme3.equals(meme4));
		System.out.println("User Equals (False): " + user1.equals(user2));
		System.out.println("User Equals (True): " + user4.equals(user5));
		System.out.println("Rating Equals (False): " + rating1.equals(rating2));
		System.out.println("Rating Equals (True): " + rating3.equals(rating4));
		
		
	}
}
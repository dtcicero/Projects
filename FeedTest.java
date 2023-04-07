/*Test for getNewMeme(User user)
 * AUTHORS: Luke Farnan, Arie Tuckerman, Daniel Cicero
 */
import java.util.ArrayList;
@Test
public void testGetNewMeme(){
	User user = new User();
	ArrayList<Meme> view = new ArrayList<Meme>();
	Meme meme1 = new Meme("meme1");
	Meme meme2 = new Meme("meme2");
	view.add(meme1);
	user.setMemesViewed(view);
	ArrayList<Meme> memes = new ArrayList<Meme>();
	memes.add(meme1);
	memes.add(meme2);
	Feed feed = new Feed();
	feed.setMemes(memes);
	
	assertEquals(meme2, feed.getNewMeme(user));
	
}

//Test for toString()
@Test
public void testToString(){
	Meme meme1 = new Meme("meme1");
	Meme meme2 = new Meme("meme2");
	ArrayList<Meme> memes = new ArrayList<Meme>();
	memes.add(meme1);
	memes.add(meme2);
	Feed feed = new Feed();
	feed.setMemes(memes);
	String expected = meme1 + "\n" + meme2 + "\n";
	assertEquals(expected, feed.toString());
}

//Test for getMemes()
@Test
public void testGetMemes(){
	Meme meme1 = new Meme("meme1");
	Meme meme2 = new Meme("meme2");
	ArrayList<Meme> memes = new ArrayList<Meme>();
	memes.add(meme1);
	memes.add(meme2);
	Feed feed = new Feed();
	feed.setMemes(memes);
	assertEquals(memes, feed.getMemes());
}

//Test for setMemes(ArrayList<Meme> meme)
@Test
public void testSetMemes(){
	Meme meme1 = new Meme("meme1");
	Meme meme2 = new Meme("meme2");
	ArrayList<Meme> memes = new ArrayList<Meme>();
	memes.add(meme1);
	memes.add(meme2);
	Feed feed = new Feed();
	feed.setMemes(memes);
	assertEquals(memes, feed.getMemes());
}

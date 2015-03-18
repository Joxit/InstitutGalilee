import scala.xml.XML, scala.concurrent._, ExecutionContext.Implicits.global, scala.util.Random
object xml extends App {

	val f: Future[scala.xml.Elem] = Future {
		XML.load("http://news.google.fr/news?pz=1&cf=all&ned=fr&hl=fr&topic=h&num=30&output=rss")
	}

	f.onSuccess {
		case x =>
			println("Devinez les titres originaux:");
			for {
				t <- (x \\ "item" \ "title")
				val a = Random.shuffle(t.text.filter { x => (x.isSpaceChar || x.isLetter) }.split(" +").toList)
			} println(a.foldRight("")((s, res) => s + " " + res))
			System.exit(0)
	}
	while (true) { ; }
}

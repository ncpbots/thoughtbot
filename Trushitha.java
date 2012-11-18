import robotics.AdaGraces;

public final class Trushitha extends adaGracesMember
{
	private final boolean TRU = true;
	private final Member ALVIN = new roboticsMember(9001);
	
	public void doSomething()
	{
		while (TRU)
		{
			// Body is intentionally left blank.
		}
	}
	
	public void hug(Member[] targets)
	{
		for(Member m: targets)
		{
			if (m.compareTo(ALVIN) == 1)
				super.jellyfish();
		}
	}
}
import java.util.*;
public class Blockchain
{
	public class Block
	{
		public String previousHash;
		public String data;
		public Block(String _data, String _previousHash)
		{
			this.data = _data;
			this.previousHash = _previousHash;
		}
		public String getHash()
		{
			return Sha.hash256(this.previousHash + this.data);
		}
		public String toString()
		{
			return String.format(" dataValue:\t %s\n previousHash:\t %s\n currrentHash:\t %s\n", this.data, this.previousHash, this.getHash());
		}
	}

	public List<Block> blocks;
	public void add(String _data)
	{
		Block previousBlock = this.blocks.get(this.blocks.size()-1);
		this.blocks.add(new Block(_data, previousBlock.getHash()));
	}
	public Blockchain()
	{
		this.blocks = new ArrayList<Block>();
		this.blocks.add(new Block("GENESIS", Sha.hash256("GENESIS")));
	}
}

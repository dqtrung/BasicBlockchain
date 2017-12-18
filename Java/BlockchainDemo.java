import java.util.*;
public class BlockchainDemo
{
	public static boolean verify(Blockchain _blockchain)
	{
		Blockchain.Block previousBlock = _blockchain.blocks.get(0);
		boolean res = true;
		for(int i = 1; i < _blockchain.blocks.size(); i++)
		{
			Blockchain.Block currentBlock = _blockchain.blocks.get(i);
			if ( !previousBlock.getHash().equals(currentBlock.previousHash) )
			{
				System.out.println("\t\tBROKEN");
				res = false;
			}

			System.out.println(currentBlock.toString());

			previousBlock = _blockchain.blocks.get(i);
		}
		return res;
	}
	public static void main(String args[])
	{
		Blockchain blockchain = new Blockchain();
		List<String> datas = new ArrayList<String>();
		for(int i=0; i<=10; i++)
		{
			datas.add(Integer.toString(i));
		}

		datas.forEach(_data -> blockchain.add(_data));

	//	blockchain.blocks.forEach(_block -> System.out.println(_block.toString()));
		
		blockchain.blocks.get(4).data = "12345";

		verify(blockchain);
	}
}

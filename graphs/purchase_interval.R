setwd("/Users/tian19880220/workspace/data/purchase_interval_data/purchase-100-120-1year-not-self-peroid/graphs")
#setwd("/Users/tian19880220/workspace/data/purchase_interval_data/purchase-40-55-1year-top7.5w/graphs")
con <- file("/Users/tian19880220/workspace/data/purchase_interval_data/purchase-100-120-1year-not-self-peroid/purchase-100-120-1year-id-uniq-sort-interval-product-notself-for-graph")
#con <- file("/Users/tian19880220/workspace/data/purchase_interval_data/purchase-40-55-1year/purchase-40-55-1year-id-uniq-sort-interval-product-for-graph")
num=0
lines = readLines(con)
for(line in lines){
	num = num +1
	print(num)
	items<-strsplit(line,split=" ")
	source_item = items[[1]][1]
	target_item = items[[1]][2]
	times<-strsplit(items[[1]][3],split=",")
	data = vector()
	for(time in times){
		data=append(data,as.numeric(time))
	}
	title = paste(source_item,target_item,sep = "-")
	title = paste(title,".jpeg",sep="")
	jpeg(file=title)
	hist(data,breaks=100,xlab="interval",ylab="frequency",col="lightblue",main=title)
	dev.off()
}


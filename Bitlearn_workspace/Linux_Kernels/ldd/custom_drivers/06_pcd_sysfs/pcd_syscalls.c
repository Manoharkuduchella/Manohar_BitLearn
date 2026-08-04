#include "pcd_platform_driver_dt_sysfs.h"

loff_t ch_lseek(struct file *filp, loff_t offset, int whence)
{
	struct ch_dev_private_data *ch_dev_pv_data = (struct ch_dev_private_data*)filp->private_data;
	
	int max_size = ch_dev_pv_data->pdata.size;

	loff_t temp;

	pr_info("lseek requested\n");
	pr_info("%s : Current value of file position = %lld\n",__func__,filp->f_pos);

	switch (whence)
	{
		case SEEK_SET:
			if( (offset > max_size)||(offset < 0) )
				return -EINVAL;
			filp->f_pos = offset; break;
		case SEEK_CUR:
			temp = filp->f_pos + offset;
			if( (temp > max_size) || (temp < 0) )
				return -EINVAL;
			filp->f_pos += offset; break;
		case SEEK_END:
			temp = max_size + offset;
			if( (temp > max_size) || ( temp < 0) )
				return -EINVAL;
			filp->f_pos = max_size + offset; break;
		default:
			return -EINVAL;
	}

	pr_info("%s : New value of the file position = %lld\n",__func__,filp->f_pos);

	return filp->f_pos;

	return 0;

}

ssize_t ch_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	struct ch_dev_private_data *ch_dev_pv_data = (struct ch_dev_private_data*)filp->private_data;
	
	int max_size = ch_dev_pv_data->pdata.size;

	pr_info("read requested for %zu bytes\n",count);
	pr_info("%s : Current file position = %lld\n",__func__,*f_pos);

	if(*f_pos + count > max_size)
		count = (max_size - *f_pos);

	if(copy_to_user(buff,ch_dev_pv_data->buffer+(*f_pos),count))
	{
		return -EFAULT;
	}

	*f_pos += count;

	pr_info("Number of bytes successfully read = %zu\n",count);
	pr_info("%s : Updated file position = %lld\n",__func__,*f_pos);

	return count;

}

ssize_t ch_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{

	struct ch_dev_private_data *ch_dev_pv_data = (struct ch_dev_private_data*)filp->private_data;
	
	int max_size = ch_dev_pv_data->pdata.size;

	pr_info("write requested for %zu bytes\n",count);
	pr_info("%s : Current file position = %lld\n",__func__,*f_pos);

	if(*f_pos + count > max_size)
		count = (max_size - *f_pos);

	if(!count)
	{
		pr_err("%s : No space left on the device\n",__func__);
		return -ENOMEM;
	}

	if(copy_from_user(ch_dev_pv_data->buffer+(*f_pos),buff,count))
	{
		return -EFAULT;
	}

	*f_pos += count;

	pr_info("Number of bytes successfully written = %zu\n",count);
	pr_info("%s : Updated file position = %lld\n",__func__,*f_pos);

	return count;

	
}



int check_permission(int dev_perm,int acc_mode)
{
	if(dev_perm == RDWR)
		return 0;

	if( (dev_perm == RDONLY) && (acc_mode & FMODE_READ) && !(acc_mode & FMODE_WRITE) )
		return 0;

	if( (dev_perm == WRONLY) && (acc_mode & FMODE_WRITE) && !(acc_mode & FMODE_READ) )
		return 0;

	return -EPERM;

}

int ch_open(struct inode *pinode, struct file *filp)
{

	int ret;
	int minor_n;

	struct ch_dev_private_data *ch_dev_pv_data; 

	minor_n = MINOR(pinode->i_rdev);
	pr_info("%s : minor access = %d\n",__func__,minor_n);

	//to get address of parent struct by using its member
	ch_dev_pv_data = container_of(pinode->i_cdev,struct ch_dev_private_data,ch_dev);

	//supply this parent struct to other file operations as well by using void *private_data of struct file
	filp->private_data = ch_dev_pv_data;

	ret = check_permission(ch_dev_pv_data->pdata.perm,filp->f_mode);

	(!ret)? pr_info("open was successfull\n") : pr_info("open was unsuccessfull\n");

	
	return ret;

}

        
int ch_release(struct inode *pinode, struct file *filp)
{
	pr_info("release was successfull\n");
	return 0;
}


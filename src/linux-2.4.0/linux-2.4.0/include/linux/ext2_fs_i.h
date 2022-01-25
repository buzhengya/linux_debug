/*
 *  linux/include/linux/ext2_fs_i.h
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/include/linux/minix_fs_i.h
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#ifndef _LINUX_EXT2_FS_I
#define _LINUX_EXT2_FS_I

/*
 * second extended file system inode data in memory
 */
struct ext2_inode_info { // inode 映射到ext2_inode
	__u32	i_data[15];
	__u32	i_flags;
	__u32	i_faddr;
	__u8	i_frag_no;
	__u8	i_frag_size;
	__u16	i_osync;
	__u32	i_file_acl;
	__u32	i_dir_acl;
	__u32	i_dtime;
	__u32	not_used_1;	/* FIX: not used/ 2.2 placeholder */
	__u32	i_block_group;
	__u32	i_next_alloc_block; // 该文件中下一个待分配的block号
	__u32	i_next_alloc_goal; // 文件所在设备中下一个待分配的block号
	__u32	i_prealloc_block; // 设备中预分配块的首个可用块号
	__u32	i_prealloc_count; // 预分配块的数量
	__u32	i_high_size;
	int	i_new_inode:1;	/* Is a freshly allocated inode */
};

#endif	/* _LINUX_EXT2_FS_I */

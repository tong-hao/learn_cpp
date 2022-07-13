## 参考资料
- https://mpitutorial.com/
- 图书《Using MPI》《Parallel Programming with MPI》《An Introduction to Parallel Programming》《MPI-The Complete Reference》
- mpi接口文档： https://www.open-mpi.org/doc/v4.0/
- openmpi架构：https://aosabook.org/en/openmpi.html


### 编译与运行
```
mpicc -o helloword _01_helloworld.c
mpirun -np 4 helloword
```

## 代码列表
| 代码文件 | 功能点 |
| -------- | ------ |
| _01_helloworld.c | MPI_Init, MPI_Comm_size, MPI_Comm_rank, MPI_Get_processor_name, MPI_Finalize |
| _02_send_recv.c  | MPI_Send, MPI_Recv |
| _03_ping_pong.c  |        |
| _04_ring.c       |        |
| _05_check_status.c  | MPI_Get_count       |
| _06_probe.c         | MPI_Probe           |
| _07_random_walk.cc  | MPI_Send, MPI_Recv  |
| _08_my_bcast.c      |                      |
| _09_compare_bcast.c | MPI_Wtime, MPI_Barrier, MPI_Bcast |
| _10_avg.c           | MPI_Scatter, MPI_Gather |
| _11_all_avg.c       | MPI_Allgather | 
| _12_random_rank.c   |               |
| _13_reduce_avg.c    | MPI_Reduce         |
| _14_reduce_stddev.c | MPI_Allreduce      |
| _15_split.c         | MPI_Comm_split     |
| _16_groups.c        | MPI_Comm_group, MPI_Group_incl, MPI_Comm_create_group, MPI_Group_free |


## MPI常用函数

### MPI_Init
```
#include <mpi.h>
int MPI_Init(int *argc, char ***argv)
```

### MPI_Comm_size
MPI_Comm_size(MPI_COMM_WORLD, &world_size);

### MPI_Comm_rank
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

### MPI_Get_processor_name
int MPI_Get_processor_name(char *name, int *resultlen)

### MPI_Finalize
MPI_Finalize();

### MPI_Abort
MPI_Abort(MPI_Comm comm, int errorcode)

### MPI_Send

MPI_Send( 
void* data,
int count,
MPI_Datatype datatype,
int destination,
int tag,
MPI_Comm communicator)

### MPI_Recv

MPI_Recv( 
void* data,
int count,
MPI_Datatype datatype, 
int source,
int tag,
MPI_Comm communicator, 
MPI_Status* status)

### MPI_Wtime
double MPI_Wtime()

### MPI_Barrier
MPI_Barrier(MPI_Comm comm)

### MPI_Bcast
MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)

### MPI_Scatter
MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
注意：该函数对于root进程则发送功能，其他进程为接收功能

### MPI_Gather
MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
注意：该函数对于其他进程为发送，root进程进行接收

### MPI_Allgather

MPI_Allgather (
void* send_data,
int send_count,
MPI_Datatype send_datatype, void* recv_data,
int recv_count,
MPI_Datatype recv_datatype, MPI_Comm communicator
)


### MPI_Reduce

MPI_Reduce(
void* send_data,
void* recv_data,
int count,
MPI_Datatype datatype, MPI_Op op,
int root,
MPI_Comm communicator)

### MPI_Allreduce

MPI_Allreduce(
void* send_data,
 void* recv_data,
int count,
MPI_Datatype datatype, MPI_Op op,
MPI_Comm communicator)

### MPI_Comm_split

MPI_Comm_split( MPI_Comm comm,
int color,
int key,
MPI_Comm* newcomm)

### MPI_Comm_create

MPI_Comm_create( MPI_Comm comm,
MPI_Group group,MPI_Comm* newcomm)

### MPI_Comm_create_group
MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm)

### MPI_Comm_group
MPI_Comm_group(MPI_Comm comm, MPI_Group* group)


### MPI_Group_union

MPI_Group_union(
MPI_Group group1,
MPI_Group group2,
MPI_Group* newgroup
)

### MPI_Group_intersection

MPI_Group_intersection(
MPI_Group group1, 
MPI_Group group2, 
MPI_Group* newgroup
)

### MPI_Group_incl

MPI_Group_incl( 
MPI_Group group,
int n,
const int ranks[], 
MPI_Group* newgroup
)

### MPI_Comm_create_group
int MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *newcomm)

### MPI_Group_free
MPI_Group_free(MPI_Group *group)

### MPI_MAX
[ MPI_MAX] maximum
[ MPI_MIN] minimum
[ MPI_SUM] sum
[ MPI_PROD] product
[ MPI_LAND] logical and
[ MPI_BAND] bit-wise and
[ MPI_LOR] logical or
[ MPI_BOR] bit-wise or
[ MPI_LXOR] logical xor
[ MPI_BXOR] bit-wise xor
[ MPI_MAXLOC] max value and location
[ MPI_MINLOC] min value and location






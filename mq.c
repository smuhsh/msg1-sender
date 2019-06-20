
1

2

3

4

5

6

7

8

9

10

11

12

13

14

15

16

17

18

19

20

21

22

23

24

25

26

27

28

29

30

31

32

33

34

35

36

37

38

39

40

41

42

43

44

45

46

47

48

49

50

51

52

53

54

55

56

57

58

59

60

61

62

63

64

65

66

67

68

69

70

71

72

73

74

75

76 


#include <stdio.h>

#include <stdlib.h>

#include <stdint.h>

#include <fcntl.h>

#include <mqueue.h>

 

void server_function()

{

	    struct mq_attr attr;

		    attr.mq_maxmsg = 10;

			    attr.mq_msgsize = 10;

				    char result[10];

					    mqd_t mfd;

						    mfd = mq_open("/mymq", O_RDWR | O_CREAT, 555, &attr);

							    if(mfd == -1)

									    {

											        perror("Server mq open error\n");

													        exit(0);

															    }

								    while(1)

										    {

												        if((mq_receive(mfd, result, attr.mq_msgsize, NULL)) == -1)

															        {

																		            perror("Server Receive error\n");

																					            exit(-1);

																								        }

														        printf("Read Data %s\n", result);

																    }

}

 

void client_function()

{

	    struct mq_attr attr;

		    attr.mq_maxmsg = 10;

			    attr.mq_msgsize = 10;

				    char buf[10] = "";

					    mqd_t mfd;

						    mfd = mq_open("/mymq", O_WRONLY, 555, &attr);

							    if(mfd == -1)

									    {

											        perror("Client mq open error\n");

													    }

								    while(1)

										    {

												        printf("INPUT DATA: ");

														        scanf("%s", buf);

																        if((mq_send(mfd, buf, attr.mq_msgsize, 1)) == -1)

																			        {

																						            perror("Client Send error\n");

																									            exit(-1);

																												        }

																		    }

}

 

int main(int argc, char** argv)

{

	    int32_t pid = fork();

		 

		    if(pid > 0)

				    {

						        printf("Parents Process: %d, %d\n", getpid(), pid);

								        server_function();

										    }

			    else if(pid == 0)

					    {

							        printf("Child Process: %d, %d\n", getpid(), pid);

									        client_function();

											    }

				    else if(pid == -1)

						    {

								        perror("fork error : ");

										        exit(0);

												    }

					 

					    return 0;

} 

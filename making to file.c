void printInstructions_tofile(int j){
	struct instruction* temp = NULL;
	temp = instructions;
	unsigned int i=0;
	printf("\n^^^^^^^^^^^^^ Start printing Instruction Table ^^^^^^^^^^^^^\n");
	while(temp <= (instructions+nextinstructionlabel()-1)){
		printf("%d:",i);
		printInstrOp(temp->opcode,j);
		if(&temp->arg1){
			printVMarg(&temp->arg1,j);			
		}
		if(&temp->arg2){
			printVMarg(&temp->arg2,j);
		}
		if(&temp->result){
			printVMarg(&temp->result,j);
		}
		i++;
		temp = instructions+i;
		printf("\n");
	}
}




void printVMarg_tofile(struct vmarg* arg,int i){ 
		
		char buf[5];
		switch(arg->type){
		case label_a: 
			      sprintf(buf,"%d,%d\t",arg->type,arg->val);
			      write(i,buf,strlen(buf));
			      break; //	label_a
		case global_a: 	sprintf(buf,"%d,%d\t",arg->type,arg->val);
				write(i,buf,strlen(buf));
				break; //	global_a
		case formal_a:	sprintf(buf,"%d,%d\t",arg->type,arg->val);
				write(i,buf,strlen(buf)); 
				break; //	formal_a
		case local_a: 	sprintf(buf,"%d,%d\t",arg->type,arg->val);
				write(i,buf,strlen(buf));
				break; //	local_a
		case number_a: 	sprintf(buf,"%d,%d\t",arg->type,arg->val);
				write(i,buf,strlen(buf));
				break; //	number_a
		case string_a: 	sprintf(buf,"%d,%d\t",arg->type,arg->val);
				write(i,buf,strlen(buf));
				break; //	string_a
		case bool_a: 	sprintf(buf,"%d,%d\t",arg->type,arg->val);
				write(i,buf,strlen(buf));
				break; //	bool_a
		case nil_a: 	sprintf(buf,"%d,%d\t",arg->type,arg->val);
				write(i,buf,strlen(buf));
				break; //nil_a
		case userfunc_a: sprintf(buf,"%d,%d\t",arg->type,arg->val);
				  write(i,buf,strlen(buf));
				  break; //	userfunc_a
		case libfunc_a:  sprintf(buf,"%d,%d\t",arg->type,arg->val);
				  write(i,buf,strlen(buf));
				  break; //	libfunc_a
		case retval_a: 	sprintf(buf,"%d,%d\t",arg->type,arg->val);
				write(i,buf,strlen(buf));
				break; //	retval_a
		default: ;//printf("Asserting for arg->val=%d\n",arg->val);assert(0);
	}
}

void printInstrOp_tofile(enum vmopcode op,int i){
	char buf[1];
	switch(op){
		case assign_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case add_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case sub_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case mul_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case div_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case mod_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case uminus_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case and_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case or_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case not_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case jump_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case jeq_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case jne_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case jle_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case jge_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case jlt_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case jgt_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case call_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case pusharg_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case funcenter_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case funcexit_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case newtable_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case tablegetelem_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case tablesetelem_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
		case nop_v:
			sprintf(buf,"%d\t",op);
			write(i,buf,strlen(buf));
			break;
	}
}
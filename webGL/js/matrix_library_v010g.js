/* -------------------------------------------------------------------------- */
/*
 |       matrix_library_v010g.js
 |       Var.0.1.0 -g
 */
/* -------------------------------------------------------------------------- */
/*
 * 2007/05/13 Object,add,sub,mul����
 * 2007/09/01 [Ver.0.1]����
 *
*/


/*
 * Ver.0.1.0 -g ��Matrix�I�u�W�F�N�g�̒l���O���[�o���ɎQ�Ƃł���^�C�v�ł��B
*/


/*********************************************/
/*                Matrix                     */
/*********************************************/
/*
 *ary��2���z�����́B2���z���1���ڂ��s�ł���A2���ڂ���ƂȂ�B
 *col,row�͎w�肵�Ȃ��Ă��\�B�z��̍s�Ɨ��ݒ�ł���B
 *���̓p�^�[���͎���3��ނ��\�ł���B
 * new Matrix( ary );       //���͂��ꂽ2���z�񂩂�s��object�𐶐�
 * new Matrix( [],col,row );//���͂��ꂽ�T�C�Y�̒P�ʍs��𐶐�
 * new Matrix( [],col );    //���͂��ꂽ�T�C�Y�̒P�ʐ����s��𐶐�
 * new Matrix();            //���̎w����Ȃ��ꍇ�A�����I��2���̐����P�ʍs��𐶐�
 * �A���A���͂��ꂽ2���z�񂪕s�ψ�ł������ꍇ�A�P�ʍs����x�[�X�Ƃ����l�ŕ⊮�����B
*/
Matrix = function( ary,_col,_row )
{
	this.col;
	this.row;
	this.isSqu;
	this.val = new Array();
	
	var _isE;
	if( !ary||!ary.length )
	{
		this.col = 2;
		this.row = 2;
		_isE = true;
	}else {
		_isE = false;
		this.col = ary.length;
		this.row = ary[0].length;
	}
	if( _col )
	{
		this.col = _col;
		this.row = _col;
	}
	if( _row )this.row = _row;
	
	this.isSqu = (this.col==this.row);
	var i,j;
	for( i=0; i<this.col; i++ )
	{
		this.val[i] = new Array();
		for( j=0; j<this.row; j++ )
			if( !_isE )this.val[i][j] = ary[i][j];
			else if( i==j )this.val[i][j] = 1;
				else this.val[i][j] = 0;
	}
	delete i;
	delete j;
	delete _col;
	delete _row;
	delete ary;
	delete _isE
}


/*********************************************/
/*                Scal                       */
/*********************************************/
/*
 *�v���g�^�C�v�֐��Ƃ��Ďg�p�B�^����ꂽ�s�񎮂��X�J���[�{����B
*/
Matrix.prototype.Scal = function( p )
{
	if( p=="" || typeof p != "number" )p = 0;
	var i,j;
	for( i=0; i<this.col; i++ )
		for( j=0; j<this.row; j++ )
			this.val[i][j] *= p;
}


/*********************************************/
/*                Add                        */
/*********************************************/
/*
 *������2�̍s�񎮂��w�肵�A���Z����Bcol,row�̒l���قȂ�ꍇ�A�v�Z�s�B
*/
Matrix.Add = function( M1,M2 )
{
	if( !(M1.col==M2.col&&M1.row==M2.row) )return undefined;
	
	var col = M1.col;
	var row = M1.row;
	var M3 = new Matrix( [],col,row );
	var i,j;
	for( i=0; i<col; i++ )
		for( j=0; j<row; j++ )
			M3.val[i][j] = M1.val[i][j] + M2.val[i][j];
	return M3;
}


/*********************************************/
/*                Sub                        */
/*********************************************/
/*
 *������2�̍s�񎮂��w�肵�A���Z����Bcol,row�̒l���قȂ�ꍇ�A�v�Z�s��undefined���o�́B
*/
Matrix.Sub = function( M1,M2 )
{
	if( !(M1.col==M2.col&&M1.row==M2.row) )return undefined;
	
	var M3 = new Matrix( [],M1.col,M1.row );
	var i,j;
	for( i=0; i<M1.col; i++ )
		for( j=0; j<M1.row; j++ )
			M3.val[i][j] = M1.val[i][j] - M2.val[i][j];
	return M3;
}


/*********************************************/
/*                Mul                        */
/*********************************************/
/*
 *������2�̍s�񎮂��w�肵�A��Z����BM1�̗�,M2�̍s�����������̂݉\�B
*/
Matrix.Mul = function( M1,M2 )
{
	if( M1.row!=M2.col )return undefined;
	
	var M3 = new Matrix( [],M1.col,M2.row );
	var i,j,k,tmp;
	for( i=0; i<M1.col; i++ )
		for( j=0; j<M2.row; j++ )
		{
			tmp = 0;
			for( k=0; k<M2.col; k++ )tmp += M1.val[i][k] * M2.val[k][j];
			M3.val[i][j] = tmp;
		}
	return M3;
}


/*********************************************/
/*                Squ                        */
/*********************************************/
/*
 *�s���2�悷��B�����s��̂ݗL���ŁA����ȊO�ł�undefined��Ԃ��B
*/
Matrix.prototype.Squ = function()
{
	if( !this.isSqu )return undefined;
	
	var MX = new Matrix( [],this.col,this.row );
	var i,j,k,tmp;
	for( i=0; i<this.col; i++ )
		for( j=0; j<this.row; j++ )
		{
			tmp = 0;
			for( k=0; k<this.col; k++ )tmp += this.val[i][k] * this.val[k][j];
			MX.val[i][j] = tmp;
		}
	return MX;
}


/*********************************************/
/*                Determinant                */
/*********************************************/
/*
 *�s�񎮂��v�Z����B�s�񂪐����s��ł͂Ȃ��ꍇ�Aundefined��Ԃ��B
 *Determinant�v���g�^�C�v�֐��͗^����ꂽ�s��̍s�񎮂�Ԃ��B
 *Determinant�v���g�^�C�v�֐������Ŏ��s�����Permutation�֐��͏�������߂�B
 *�܂��APermutation�֐��ł͈�x�v�Z���������̌v�Z���ʂ̓L���b�V���������B
*/
Matrix.prototype.Determinant = function()
{
	if( !this.isSqu )return undefined;
	var PerList = Matrix.Permutation( this.col );
	var dete = 0;
	var i,j,tmp,n_list
	for( i=0; i<PerList.length; i++ )
	{
		n_list = PerList[i];
		tmp = n_list[0];
		for( j=0; j<n_list[1].length; j++ )tmp *= this.val[j][n_list[1][j]];
		dete += tmp;
	}
	return dete;
}

/* Permutation�����߂� */
Matrix.Permutation = function( input )
{
	if( Matrix.Permutation.isCatch[input] )return Matrix.Permutation.Catch[input];
	var ary = new Array();
	for( var i=0; i<input; i++ )ary[i] = new String(i);
	var list = Matrix.Permutation.Ext( "",ary,input );
	var PerL = new Array();//�`�� [����,Number,Number,Number,Number,...]
	var tmp,j;
	for( i=0; i<list.length; i++ )
	{
		tmp = new Array();
		for( j=0; j<list[i].length; j++ )tmp[j] = list[i].charAt(j);
		var flag = Matrix.Functype( tmp.Copy() );
		PerL[i] = [flag,tmp];
	}
	Matrix.Permutation.Catch[input] = PerL;
	Matrix.Permutation.isCatch[input] = true;
	return PerL;
}

Matrix.Permutation.Ext = function( aryout,aryin,max )
{
	if( aryout.length==max )return aryout;
	else{
		var aryco = new Array();
		var aryR = new Array();
		for(var i=0; i<aryin.length; i++)
			aryco[i] = Matrix.Permutation.Ext( aryout+aryin[i], aryin.PointDel(i), max );
		if( max-aryout.length>1 )for(var j=0; j<aryco.length; j++)aryR = aryR.concat(aryco[j]);
		else aryR = aryco;
		return aryR;
	}
}
Matrix.Permutation.Catch = [null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null];
Matrix.Permutation.isCatch = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];

/* ���֐�,��֐��𔻕ʂ��� */
Matrix.Functype = function( ary )
{
	var cnt = 0;
	var move = true;
	var i,tmp;
	while( move )
	{
		move = false;
		for( i=0; i<ary.length-1; i++ )
		{
			tmp = [ ary[i],ary[i+1] ];
			if( tmp[0]>tmp[1] )
			{
				ary[i] = tmp[1];
				ary[i+1] = tmp[0];
				cnt++;
				move = true;
			}
		}
	}
	if( cnt%2==0 )return 1;
	else return -1;
}
/*
var r = Permutation( "",["1","2","3","4"],4 );
for(var i=0; i<r.length; i++)document.writeln(r[i]);
*/


/*********************************************/
/*                 Inverse                   */
/*********************************************/
/*
 *�t�s����v�Z����B�s�񂪐����s��ł͂Ȃ��ꍇ�Aundefined��Ԃ��B
 *Inverse�v���g�^�C�v�֐��͗^����ꂽ�s��̋t�s���Ԃ��B
 *Inverse�v���g�^�C�v�֐��̎��s�ɂ͍s�񎮂��v�Z����Determinant�v���g�^�C�v�֐����K�v�B
 *�t�s�񂪑��݂��Ȃ��ꍇ�ɂ́A�v�Z�s�\��undefined�Ƃ͕ʂ�0��Ԃ��B
*/
Matrix.prototype.Inverse = function()
{
	if( !this.isSqu )return undefined;
	var _A = this.Determinant();
	if( _A==0 )return 0;
	
	var len = this.col;
	var i,j,k,l,k_v,l_v,tmp,flag;
	var flag_def = 1;
	var output = new Matrix([],len);
	for(i=0; i<len; i++)
	{
		flag = flag_def;
		for(j=0; j<len; j++)
		{
			tmp = new Matrix([],len-1);
			k_v = 0;
			for(k=0; k<len; k++)
			{
				if( k==i )continue;
				l_v = 0;
				for(l=0; l<len; l++)
				{
					if( l==j )continue;
					tmp.val[k_v][l_v] = this.val[k][l];
					l_v++;
				}
				k_v++;
			}
			output.val[j][i] = flag * tmp.Determinant();
			flag *= -1;
		}
		flag_def *= -1;
	}
	output.Scal( 1/_A )
	return output;
}


/*********************************************/
/*                Print                      */
/*********************************************/
/*
 *�s�񎮂𕶎���Ƃ��Đ��`����B������true�������HTML���[�h(\n��<br>\n�ɂȂ�)�B
*/
Matrix.prototype.Print = function( isHTML )
{
	var br = "\n";
	switch (isHTML)
	{
		case 1 : br = "<br>\n";break;
		case 2 : br = "<br />\n";break;
		default:break;
	}
	var i,j;
	var str = new String();
	for( i=0; i<this.col; i++ )
	{
		str += "["
		for( j=0; j<this.row; j++ )
		{
			str += this.val[i][j];
			if( j+1<this.row )str += ",";
		}
		str += "]" + br;
	}
	return str;
}


/*********************************************/
/*                prototype                  */
/*********************************************/
/*
 *�K�v�ȃf�t�H���g�I�u�W�F�N�g��prototype�֐����`
*/
Array.prototype.PointDel = function( point )
{
	var first = this.slice(0,point);
	var last = this.slice(point+1,this.length);
	return first.concat(last);
}
Array.prototype.Copy = function()
{
	var new_array = new Array( this.length );
	for( var i=0 ; i<this.length ; i++ )new_array[i] = this[i];
	return new_array;
}
#pragma once
#ifndef CALLBACK_H
#define CALLBACK_H

#define CB_ERR 0		//Constantes de error y 
#define CB_SUXS 1		//exito para este archivo

//esta funcion valida 
int parseCallBack(const char* key, const char* value, void* datosDeUsuario);


#endif // !CALLBACK_H
